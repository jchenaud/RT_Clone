/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/23 12:35:38 by pribault          #+#    #+#             */
/*   Updated: 2017/08/23 12:36:39 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IMAGES_H
# define IMAGES_H

# include <OpenCL/cl.h>
# include "types.h"

typedef struct	s_color
{
	cl_uchar	r;
	cl_uchar	g;
	cl_uchar	b;
	cl_uchar	a;
}				t_color;

typedef struct	s_img
{
	void		*ptr;
	t_color		*img;
	int			w;
	int			h;
}				t_img;

#endif
