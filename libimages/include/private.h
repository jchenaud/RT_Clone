/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   private.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/27 16:50:09 by pribault          #+#    #+#             */
/*   Updated: 2017/08/29 22:24:32 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRIVATE_H
# define PRIVATE_H

# include "types.h"

# define BMP_MAGIC	0x4d42
# define PNG_MAGIC	0x0a1a0a0d474e5089

# pragma pack(1)

typedef struct	s_png_chunk
{
	t_uint		lenght;
	char		name[4];
}				t_png_chunk;

typedef struct	s_png_ihdr
{
	t_uint		lenght;
	char		name[4];
	int			width;
	int			height;
	t_uchar		depth;
	t_uchar		color;
	t_uchar		compression;
	t_uchar		filter;
	t_uchar		method;
	t_uint		crc;
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

#endif
