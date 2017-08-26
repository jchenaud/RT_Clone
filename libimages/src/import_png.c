/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   import_png.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/24 01:15:55 by pribault          #+#    #+#             */
/*   Updated: 2017/08/24 01:47:22 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libimages.h"

char	endian(void *ptr, size_t n)
{
	size_t	i;
	char	tmp;

	i = 0;
	n--;
	while (i < n)
	{
		tmp = ((char*)ptr)[i];
		((char*)ptr)[i] = ((char*)ptr)[n];
		((char*)ptr)[n] = tmp;
		i++;
		n--;
	}
	return (1);
}

void	invert_image(t_img *new)
{
	t_color	tmp[new->w * new->h];
	int		i;
	int		j;

	i = 0;
	j = new->h - 1;
	while (i < j)
	{
		ft_memcpy(&tmp, new->img + i * new->w, sizeof(t_color) * new->w);
		ft_memcpy(new->img + i * new->w, new->img + j * new->w,
		sizeof(t_color) * new->w);
		ft_memcpy(new->img + j * new->w, &tmp, sizeof(t_color) * new->w);
		i++;
		j--;
	}
}

void	get_idat(t_png_ihdr *ihdr, t_png_chunk *chunk, t_img *new, int fd)
{
	char		buffer[chunk->lenght];
	z_stream	strm;

	ft_bzero(&strm, sizeof(z_stream));
	strm.next_in = &buffer;
	strm.avail_in = chunk->lenght;
	strm.next_out = new->img;
	strm.avail_out = sizeof(t_color) * new->w * new->h;
	read(fd, &buffer, chunk->lenght);
	inflateInit(&strm);
	inflate(&strm, Z_NO_FLUSH);
	inflateEnd(&strm);
	invert_image(new);
}

void	read_text(t_png_chunk *chunk, int fd)
{
	char	buffer[chunk->lenght];

	read(fd, &buffer, chunk->lenght);
	ft_putstr("png text: ");
	write(1, &buffer, chunk->lenght);
	ft_putchar('\n');
}

void	if_forest(t_png_ihdr *ihdr, t_png_chunk *chunk, t_img *new, int fd)
{
	ft_printf("name=%c%c%c%c len=%d\n", chunk->name[0], chunk->name[1], chunk->name[2], chunk->name[3], chunk->lenght);
	if (!ft_strncmp(chunk->name, "IDAT", 4))
		get_idat(ihdr, chunk, new, fd);
	else if (!ft_strncmp(chunk->name, "tEXt", 4))
		read_text(chunk, fd);
	else
		lseek(fd, chunk->lenght, SEEK_CUR);
}

t_img	*import_png(char *file)
{
	t_png_ihdr	ihdr;
	t_png_chunk	chunk;
	t_uint64	magic;
	t_img		*new;
	int			fd;

	if ((fd = open(file, O_RDONLY)) == -1)
		return (NULL);
	if (read(fd, &magic, sizeof(t_uint64)) != sizeof(t_uint64) ||
	magic != PNG_MAGIC || read(fd, &ihdr, sizeof(t_png_ihdr)) !=
	sizeof(t_png_ihdr) || ft_strncmp(ihdr.name, "IHDR", 4) ||
	!endian(&ihdr.width, 4) || !endian(&ihdr.height, 4) ||
	!endian(&ihdr.crc, 4) || !(new = (t_img*)malloc(sizeof(t_img))) ||
	!(new->w = ihdr.width) || !(new->h = ihdr.height) ||
	!(new->img = (t_color*)malloc(sizeof(t_color) * new->w * new->h)))
		return (NULL);
	ft_printf("w=%d h=%d depth=%u colors=%u compression=%u filter=%u method=%u\n",
	ihdr.width, ihdr.height, ihdr.depth, ihdr.color, ihdr.compression, ihdr.filter, ihdr.method);
	while (read(fd, &chunk, sizeof(t_png_chunk)) == sizeof(t_png_chunk) &&
	endian(&chunk.lenght, 4))
	{
		if_forest(&ihdr, &chunk, new, fd);
		lseek(fd, 4, SEEK_CUR);
	}
	return (new);
}
