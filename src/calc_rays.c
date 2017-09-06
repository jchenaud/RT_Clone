/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/06 10:13:26 by pribault          #+#    #+#             */
/*   Updated: 2017/09/06 10:15:49 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		*calculate_rays(t_cl *cl, void *rays, void *intersecs, size_t p)
{
	cl_mem	intersecs_mem;
	cl_mem	rays_mem;
	cl_mem	new_mem;
	cl_int	err;

	new_mem = clCreateBuffer(cl->context, CL_MEM_ALLOC_HOST_PTR,
	sizeof(t_ray) * p * 2, NULL, &err);
	if (err != CL_SUCCESS)
		error(48, 1, &err);
	rays_mem = clCreateBuffer(cl->context, CL_MEM_COPY_HOST_PTR,
	sizeof(t_ray) * p, rays, &err);
	if (err != CL_SUCCESS)
		error(48, 1, &err);
	intersecs_mem = clCreateBuffer(cl->context, CL_MEM_COPY_HOST_PTR,
	sizeof(t_intersec) * p, intersecs, &err);
	if (err != CL_SUCCESS)
		error(48, 1, &err);
	if ((err = clSetKernelArg(cl->calc_rays, 0, sizeof(cl_mem),
	&new_mem)) != CL_SUCCESS)
		error(49, 1, &err);
	if ((err = clSetKernelArg(cl->calc_rays, 1, sizeof(cl_mem),
	&rays_mem)) != CL_SUCCESS)
		error(49, 1, &err);
	if ((err = clSetKernelArg(cl->calc_rays, 2, sizeof(cl_mem),
	&intersecs_mem)) != CL_SUCCESS)
		error(49, 1, &err);
	if ((err = clSetKernelArg(cl->calc_rays, 3, sizeof(cl_mem),
	&cl->n_obj_mem)) != CL_SUCCESS)
		error(49, 1, &err);
	if ((err = clSetKernelArg(cl->calc_rays, 4, sizeof(cl_mem),
	&cl->obj_mem)) != CL_SUCCESS)
		error(49, 1, &err);
	clEnqueueNDRangeKernel(cl->queue, cl->calc_rays, 1, NULL, &p,
	NULL, 0, NULL, NULL);
	if (clFinish(cl->queue) != CL_SUCCESS)
		error(52, 1, NULL);
	free(rays);
	rays = malloc(sizeof(t_ray) * p * 2);
	clEnqueueReadBuffer(cl->queue, new_mem, CL_TRUE, 0,
	sizeof(t_ray) * p * 2, rays, 0, NULL, NULL);
	if (clFinish(cl->queue) != CL_SUCCESS)
		error(52, 1, NULL);
	return (rays);
}
