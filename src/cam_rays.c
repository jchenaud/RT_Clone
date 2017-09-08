/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam_rays.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/06 06:22:56 by pribault          #+#    #+#             */
/*   Updated: 2017/09/08 04:20:26 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	*create_cam_rays(t_env *env, t_cam *cam)
{
	cl_mem	rays_mem;
	cl_mem	cam_mem;
	void	*rays;

	cam_mem = create_buffer(&env->cl, CL_MEM_COPY_HOST_PTR,
	sizeof(t_cam), cam);
	rays_mem = create_buffer(&env->cl, CL_MEM_ALLOC_HOST_PTR,
	sizeof(t_ray) * cam->w * cam->h, NULL);
	set_kernel_arg(&env->cl.cam_rays, &cam_mem, 0);
	set_kernel_arg(&env->cl.cam_rays, &rays_mem, 1);
	if (!(rays = (t_ray*)malloc(sizeof(t_ray) * cam->w * cam->h)))
		error(1, 1, NULL);
	nd_range_kernel(&env->cl, &env->cl.cam_rays, cam->w * cam->h);
	read_buffer(&env->cl, rays_mem, rays, sizeof(t_ray) * cam->w * cam->h);
	env->cl.rays = rays_mem;
	return (rays);
}
