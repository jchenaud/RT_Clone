/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/06 10:13:26 by pribault          #+#    #+#             */
/*   Updated: 2017/09/07 07:17:51 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		*calculate_rays(t_cl *cl, void *rays, void *intersecs, size_t p)
{
	cl_mem	intersecs_mem;
	cl_mem	rays_mem;
	cl_mem	new_mem;

	new_mem = create_buffer(cl, CL_MEM_ALLOC_HOST_PTR,
	sizeof(t_ray) * p * 2, NULL);
	rays_mem = create_buffer(cl, CL_MEM_COPY_HOST_PTR,
	sizeof(t_ray) * p, rays);
	intersecs_mem = create_buffer(cl, CL_MEM_COPY_HOST_PTR,
	sizeof(t_intersec) * p, intersecs);
	set_kernel_arg(&cl->calc_rays, &new_mem, 0);
	set_kernel_arg(&cl->calc_rays, &rays_mem, 1);
	set_kernel_arg(&cl->calc_rays, &intersecs_mem, 2);
	set_kernel_arg(&cl->calc_rays, &cl->n_obj_mem, 3);
	set_kernel_arg(&cl->calc_rays, &cl->obj_mem, 4);
	nd_range_kernel(cl, &cl->calc_rays, p);
	free(rays);
	rays = malloc(sizeof(t_ray) * p * 2);
	read_buffer(cl, new_mem, rays, sizeof(t_ray) * p * 2);
	cl->rays = new_mem;
	return (rays);
}
