/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   antialiasing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/26 23:39:24 by pribault          #+#    #+#             */
/*   Updated: 2017/09/06 07:51:34 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	create_buffers(t_cl *cl, t_resize_buff *mem, t_img *img)
{
	mem->img_src = clCreateBuffer(cl->context, CL_MEM_COPY_HOST_PTR,
	sizeof(t_img), img, &cl->error);
	if (cl->error != CL_SUCCESS)
		error(48, 1, &cl->error);
	mem->dest = clCreateBuffer(cl->context, CL_MEM_ALLOC_HOST_PTR,
	sizeof(t_color) * img->w * img->h, NULL, &cl->error);
	if (cl->error != CL_SUCCESS)
		error(48, 1, &cl->error);
	mem->src = clCreateBuffer(cl->context, CL_MEM_COPY_HOST_PTR,
	sizeof(t_color) * img->w * img->h, img->pixels, &cl->error);
	if (cl->error != CL_SUCCESS)
		error(48, 1, &cl->error);
}

static void	set_buffers(t_cl *cl, t_resize_buff *mem)
{
	if ((cl->error = clSetKernelArg(cl->antialiasing, 0, sizeof(cl_mem),
	&mem->img_src)) != CL_SUCCESS)
		error(49, 1, &cl->error);
	if ((cl->error = clSetKernelArg(cl->antialiasing, 1, sizeof(cl_mem),
	&mem->dest)) != CL_SUCCESS)
		error(49, 1, &cl->error);
	if ((cl->error = clSetKernelArg(cl->antialiasing, 2, sizeof(cl_mem),
	&mem->src)) != CL_SUCCESS)
		error(49, 1, &cl->error);
}

void		antialiase(t_uchar antialias, t_cl *cl, t_img *img)
{
	t_resize_buff	mem;
	size_t			n;
	size_t			i;

	n = img->w * img->h;
	i = 0;
	while (i++ < antialias)
	{
		create_buffers(cl, &mem, img);
		set_buffers(cl, &mem);
		clEnqueueNDRangeKernel(cl->queue, cl->antialiasing, 1, NULL, &n,
		NULL, 0, NULL, NULL);
		if (clFinish(cl->queue) != CL_SUCCESS)
			error(52, 1, NULL);
		clEnqueueReadBuffer(cl->queue, mem.dest, CL_TRUE, 0,
		n * sizeof(t_color), img->pixels, 0, NULL, NULL);
		if (clFinish(cl->queue) != CL_SUCCESS)
			error(52, 1, NULL);
	}
}
