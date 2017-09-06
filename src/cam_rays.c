/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam_rays.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/06 06:22:56 by pribault          #+#    #+#             */
/*   Updated: 2017/09/06 07:50:26 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	*create_cam_rays_2(t_env *env, t_cam *cam, cl_mem rays_mem)
{
	void	*rays;
	size_t	n;

	if (!(rays = (t_ray*)malloc(sizeof(t_ray) * cam->w * cam->h)))
		error(1, 1, NULL);
	n = cam->w * cam->h;
	clEnqueueNDRangeKernel(env->cl.queue, env->cl.cam_rays, 1, NULL, &n,
	NULL, 0, NULL, NULL);
	if (clFinish(env->cl.queue) != CL_SUCCESS)
		error(52, 1, NULL);
	clEnqueueReadBuffer(env->cl.queue, rays_mem, CL_TRUE, 0,
	n * sizeof(t_ray), rays, 0, NULL, NULL);
	if (clFinish(env->cl.queue) != CL_SUCCESS)
		error(52, 1, NULL);
	env->cl.rays = rays_mem;
	return (rays);
}

void	*create_cam_rays(t_env *env, t_cam *cam)
{
	cl_mem	rays_mem;
	cl_mem	cam_mem;
	cl_int	err;

	cam_mem = clCreateBuffer(env->cl.context, CL_MEM_COPY_HOST_PTR,
	sizeof(t_cam), cam, &err);
	if (err != CL_SUCCESS)
		error(48, 1, &err);
	rays_mem = clCreateBuffer(env->cl.context, CL_MEM_ALLOC_HOST_PTR,
	sizeof(t_ray) * cam->w * cam->h, NULL, &err);
	if (err != CL_SUCCESS)
		error(48, 1, &err);
	if ((err = clSetKernelArg(env->cl.cam_rays, 0, sizeof(cl_mem),
	&cam_mem)) != CL_SUCCESS)
		error(49, 1, &err);
	if ((err = clSetKernelArg(env->cl.cam_rays, 1, sizeof(cl_mem),
	&rays_mem)) != CL_SUCCESS)
		error(49, 1, &err);
	return (create_cam_rays_2(env, cam, rays_mem));
}
