/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_bmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/23 22:43:31 by pribault          #+#    #+#             */
/*   Updated: 2017/08/29 22:26:27 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libimages.h"
#include "private.h"

void	fill_header(t_img *img, t_bmp_fh *header)
{
	header->magic = BMP_MAGIC;
	header->size = sizeof(t_bmp_fh) + sizeof(t_bmp_dibh) +
	sizeof(t_color) * img->w * img->h;
	header->reserved = 42;
	header->offset = sizeof(t_bmp_fh) + sizeof(t_bmp_dibh);
}

void	fill_dib(t_img *img, t_bmp_dibh *dib)
{
	dib->size = sizeof(t_bmp_dibh);
	dib->width = img->w;
	dib->height = img->h;
	dib->color_planes = 1;
	dib->bpp = 32;
	dib->compression = 0;
	dib->raw_size = sizeof(t_color) * img->w * img->h;
	dib->hres = 1;
	dib->vres = 1;
	dib->colors = 0;
	dib->importants = 0;
}

void	export_bmp(t_img *img, char *file)
{
	t_bmp_fh	header;
	t_bmp_dibh	dib;
	int			fd;

	if (!img)
		return ;
	if ((fd = open(file, O_TRUNC | O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR |
	S_IRGRP | S_IROTH)) == -1)
		return ;
	fill_header(img, &header);
	fill_dib(img, &dib);
	write(fd, &header, sizeof(t_bmp_fh));
	write(fd, &dib, sizeof(t_bmp_dibh));
	write(fd, img->pixels, sizeof(t_color) * img->w * img->h);
	close(fd);
}
