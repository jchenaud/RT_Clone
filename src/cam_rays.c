/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam_rays.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/06 06:22:56 by pribault          #+#    #+#             */
/*   Updated: 2017/10/20 14:55:53 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
**	used to calculate the firsts rays starting from the camera
*/

void	create_cam_rays(t_env *env, t_cam *cam, size_t m, size_t max)
{
	cl_mem	rays_mem;
	cl_mem	cam_mem;
	cl_mem	max_mem;
	cl_mem	m_mem;

	cam_mem = create_buffer(&env->cl, CL_MEM_COPY_HOST_PTR,
	sizeof(t_cam), cam);
	rays_mem = create_buffer(&env->cl, CL_MEM_ALLOC_HOST_PTR,
	sizeof(t_ray) * cam->w * ((m == max) ? cam->h % max : cam->h / max), NULL);
	m_mem = create_buffer(&env->cl, CL_MEM_COPY_HOST_PTR, sizeof(size_t), &m);
	max_mem = create_buffer(&env->cl, CL_MEM_COPY_HOST_PTR, sizeof(size_t),
	&max);
	set_kernel_arg(&env->cl.cam_rays, &cam_mem, 0);
	set_kernel_arg(&env->cl.cam_rays, &rays_mem, 1);
	set_kernel_arg(&env->cl.cam_rays, &m_mem, 2);
	set_kernel_arg(&env->cl.cam_rays, &max_mem, 3);
	nd_range_kernel(&env->cl, &env->cl.cam_rays, cam->w * ((m == max) ?
	cam->h % max : cam->h / max));
	env->cl.rays = rays_mem;
	delete_buffer(cam_mem);
	delete_buffer(m_mem);
	delete_buffer(max_mem);
}
