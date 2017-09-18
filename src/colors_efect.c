/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_efect.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/16 10:57:55 by jchenaud          #+#    #+#             */
/*   Updated: 2017/09/18 10:52:44 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	colors_efect(t_cl *cl, t_img *image, int effect)
{
	cl_mem img;
	cl_mem col;
	cl_mem modi;
	size_t n;

	n = image->w * image->h;
	img = create_buffer(cl, CL_MEM_COPY_HOST_PTR,
	sizeof(t_img), image);
	col = create_buffer(cl, CL_MEM_COPY_HOST_PTR,
	sizeof(t_color) * image->w * image->h, image->pixels);
	modi = create_buffer(cl, CL_MEM_COPY_HOST_PTR,
	sizeof(int), &effect);
	set_kernel_arg(&cl->colors_efect, &img, 0);
	set_kernel_arg(&cl->colors_efect, &col, 1);
	set_kernel_arg(&cl->colors_efect, &modi, 2);
	nd_range_kernel(cl, &cl->colors_efect, n);
	read_buffer(cl, col, image->pixels, n * sizeof(t_color));
}
