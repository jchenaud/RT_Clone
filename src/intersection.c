/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/06 07:58:40 by pribault          #+#    #+#             */
/*   Updated: 2017/09/08 04:30:58 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		*calculate_intersections(t_env *env, size_t n)
{
	cl_mem	intersecs;
	void	*ret;

	if (!(ret = malloc(sizeof(t_intersec) * n)))
		error(1, 1, NULL);
	intersecs = create_buffer(&env->cl, CL_MEM_ALLOC_HOST_PTR,
	sizeof(t_intersec) * n, NULL);
	set_kernel_arg(&env->cl.intersection, &intersecs, 0);
	set_kernel_arg(&env->cl.intersection, &env->cl.intersecs, 1);
	set_kernel_arg(&env->cl.intersection, &env->cl.rays, 2);
	set_kernel_arg(&env->cl.intersection, &env->cl.n_obj_mem, 3);
	set_kernel_arg(&env->cl.intersection, &env->cl.obj_mem, 4);
	set_kernel_arg(&env->cl.intersection, &env->cl.n_light_mem, 5);
	set_kernel_arg(&env->cl.intersection, &env->cl.light_mem, 6);
	nd_range_kernel(&env->cl, &env->cl.intersection, n);
	read_buffer(&env->cl, intersecs, ret, sizeof(t_intersec) * n);
	env->cl.intersecs = intersecs;
	return (ret);
}
