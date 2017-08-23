/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libimages.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/23 22:42:18 by pribault          #+#    #+#             */
/*   Updated: 2017/08/24 01:37:47 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBIMAGES_H
# define LIBIMAGES_H

# include "libft.h"
# include "types.h"

# define BMP_MAGIC	0x4d42
# define PNG_MAGIC	0x0a1a0a0d474e5089

typedef struct	s_color
{
	t_uchar		b;
	t_uchar		g;
	t_uchar		r;
	t_uchar		a;
}				t_color;

typedef struct	s_img
{
	void		*ptr;
	t_color		*img;
	int			w;
	int			h;
}				t_img;

# pragma pack(1)

typedef struct	s_png_chunk
{
	t_uint		lenght;
	char		name[4];
}				t_png_chunk;

typedef struct	s_png_ihdr
{
	int			width;
	int			height;
	t_uchar		depth;
	t_uchar		color;
	t_uchar		compression;
	t_uchar		filter;
	t_uchar		method;
}				t_png_ihdr;

typedef struct	s_bmp_fh
{
	t_uint16	magic;
	t_uint32	size;
	t_uint32	reserved;
	t_uint32	offset;
}				t_bmp_fh;

typedef struct	s_bmp_dibh
{
	t_uint32	size;
	int			width;
	int			height;
	t_uint16	color_planes;
	t_uint16	bpp;
	t_uint32	compression;
	t_uint32	raw_size;
	int			hres;
	int			vres;
	t_uint32	colors;
	t_uint32	importants;
}				t_bmp_dibh;

t_img			*import_bmp(char *file);
void			export_bmp(t_img *img, char *file);

t_img			*import_png(char *file);

#endif
