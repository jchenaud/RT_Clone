/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/06 10:13:26 by pribault          #+#    #+#             */
/*   Updated: 2017/10/20 14:55:10 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
**	this function use rays.cl to calculate reflection and refraction rays 
*/

void		calculate_rays(t_cl *cl, size_t p)
{
	cl_mem	new_mem;

	new_mem = create_buffer(cl, CL_MEM_ALLOC_HOST_PTR,
	sizeof(t_ray) * p * 2, NULL);
	set_kernel_arg(&cl->calc_rays, &new_mem, 0);
	set_kernel_arg(&cl->calc_rays, &cl->rays, 1);
	set_kernel_arg(&cl->calc_rays, &cl->intersecs, 2);
	set_kernel_arg(&cl->calc_rays, &cl->n_obj_mem, 3);
	set_kernel_arg(&cl->calc_rays, &cl->obj_mem, 4);
	nd_range_kernel(cl, &cl->calc_rays, p);
	delete_buffer(cl->rays);
	cl->rays = new_mem;
}
