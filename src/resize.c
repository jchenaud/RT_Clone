/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/26 20:16:55 by pribault          #+#    #+#             */
/*   Updated: 2017/08/31 05:00:59 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		alloc_buffers(t_cl *cl, t_resize_buff *mem, t_img *dest, t_img *src)
{
	mem->img_dest = clCreateBuffer(cl->context, CL_MEM_COPY_HOST_PTR,
	sizeof(t_img), dest, &cl->error);
	if (cl->error != CL_SUCCESS)
		error(48, 1, &cl->error);
	mem->dest = clCreateBuffer(cl->context, CL_MEM_COPY_HOST_PTR,
	sizeof(t_color) * dest->w * dest->h, dest->pixels, &cl->error);
	if (cl->error != CL_SUCCESS)
		error(48, 1, &cl->error);
	mem->img_src = clCreateBuffer(cl->context, CL_MEM_COPY_HOST_PTR,
	sizeof(t_img), src, &cl->error);
	if (cl->error != CL_SUCCESS)
		error(48, 1, &cl->error);
	mem->src = clCreateBuffer(cl->context, CL_MEM_COPY_HOST_PTR,
	sizeof(t_color) * src->w * src->h, src->pixels, &cl->error);
	if (cl->error != CL_SUCCESS)
		error(48, 1, &cl->error);
}

static void	set_buffers(t_cl *cl, t_resize_buff *mem)
{
	if ((cl->error = clSetKernelArg(cl->resize, 0, sizeof(cl_mem),
	&mem->img_dest)) != CL_SUCCESS)
		error(49, 1, &cl->error);
	if ((cl->error = clSetKernelArg(cl->resize, 1, sizeof(cl_mem),
	&mem->dest)) != CL_SUCCESS)
		error(49, 1, &cl->error);
	if ((cl->error = clSetKernelArg(cl->resize, 2, sizeof(cl_mem),
	&mem->img_src)) != CL_SUCCESS)
		error(49, 1, &cl->error);
	if ((cl->error = clSetKernelArg(cl->resize, 3, sizeof(cl_mem),
	&mem->src)) != CL_SUCCESS)
		error(49, 1, &cl->error);
}

void		resize_image(t_cl *cl, t_img *dest, t_img *src)
{
	t_resize_buff	mem;
	size_t			n;

	n = dest->w * dest->h;
	alloc_buffers(cl, &mem, dest, src);
	set_buffers(cl, &mem);
	clEnqueueNDRangeKernel(cl->queue, cl->resize, 1, NULL, &n,
	NULL, 0, NULL, NULL);
	if (clFinish(cl->queue) != CL_SUCCESS)
		error(52, 1, NULL);
	clEnqueueReadBuffer(cl->queue, mem.dest, CL_TRUE, 0,
	n * sizeof(t_color), dest->pixels, 0, NULL, NULL);
	if (clFinish(cl->queue) != CL_SUCCESS)
		error(52, 1, NULL);
}

void		resize_images(t_env *env)
{
	t_img	*tmp;
	t_list	*cam;
	t_uint	n;
	t_uint	i;

	n = 0;
	cam = env->cam;
	while (cam)
	{
		n++;
		cam = cam->next;
	}
	env->n = n;
	if (!(env->img = (t_img*)malloc(sizeof(t_img) * n)))
		error(1, 1, NULL);
	i = n - 1;
	cam = env->cam;
	while (cam)
	{
		tmp = new_img(env->win->w, env->win->h);
		ft_memcpy(&env->img[i], tmp, sizeof(t_img));
		free(tmp);
		resize_image(&env->cl, &env->img[i--], ((t_cam*)cam->content)->img);
		export_bmp(&env->img[i + 1], "test.bmp");
		cam = cam->next;
	}
}
