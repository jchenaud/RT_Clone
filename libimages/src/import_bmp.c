/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   import_bmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/24 00:34:39 by pribault          #+#    #+#             */
/*   Updated: 2017/08/29 22:27:02 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libimages.h"
#include "private.h"

void	fill_image(t_img *img, t_bmp_dibh *dib, int fd)
{
	t_color	color;
	int		i;
	int		max;

	i = 0;
	max = img->w * img->h;
	ft_bzero(&color, sizeof(t_color));
	while (i < max)
		read(fd, &img->pixels[i++], dib->bpp / 8);
}

t_img	*import_bmp(char *file)
{
	t_img		*new;
	t_bmp_fh	header;
	t_bmp_dibh	dib;
	int			fd;

	if ((fd = open(file, O_RDONLY)) == -1)
		return (NULL);
	ft_bzero(&header, sizeof(t_bmp_fh));
	if (!(new = (t_img*)malloc(sizeof(t_img))) || read(fd, &header,
	sizeof(t_bmp_fh)) != sizeof(t_bmp_fh) || header.magic != BMP_MAGIC ||
	read(fd, &dib, sizeof(t_bmp_dibh)) != sizeof(t_bmp_dibh))
		return (NULL);
	new->pixels = (t_color*)malloc(sizeof(t_color) * dib.width * dib.height);
	ft_bzero(new->pixels, sizeof(t_color) * dib.width * dib.height);
	new->w = dib.width;
	new->h = dib.height;
	lseek(fd, header.offset, SEEK_SET);
	fill_image(new, &dib, fd);
	close(fd);
	return (new);
}
