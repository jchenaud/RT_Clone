/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   import_png.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/24 01:15:55 by pribault          #+#    #+#             */
/*   Updated: 2017/08/24 01:36:21 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libimages.h"

void	endian(char *ptr, size_t n)
{
	size_t	i;
	char	tmp;

	i = 0;
	n--;
	while (i < n)
	{
		tmp = ptr[i];
		ptr[i] = ptr[n];
		ptr[n] = tmp;
		i++;
		n--;
	}
}

t_img	*import_png(char *file)
{
	t_png_chunk	chunk;
	t_uint64	magic;
	int			fd;

	if ((fd = open(file, O_RDONLY)) == -1)
		return (NULL);
	if (read(fd, &magic, sizeof(t_uint64)) != sizeof(t_uint64) ||
	magic != PNG_MAGIC)
		return (NULL);
	ft_printf("magic=%lx\n", magic);
	while (read(fd, &chunk, sizeof(t_png_chunk)) == sizeof(t_png_chunk))
	{
		endian((char*)&chunk.lenght, 4);
		ft_printf("name=%c%c%c%c len=%d\n", chunk.name[0], chunk.name[1], chunk.name[2], chunk.name[3], chunk.lenght);
		lseek(fd, chunk.lenght + 4, SEEK_CUR);
	}
	return (NULL);
}
