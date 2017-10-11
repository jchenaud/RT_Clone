/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/06 07:58:40 by pribault          #+#    #+#             */
/*   Updated: 2017/10/09 20:29:25 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		calculate_intersections(t_env *env, size_t n)
{
	cl_mem	intersecs;

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
	delete_buffer(env->cl.intersecs);
	env->cl.intersecs = intersecs;
}

void		initialize_intersecs(t_env *env, t_cam *cam, size_t m, size_t max)
{
	t_intersec			*buffer;
	static t_intersec	def = {-1, 0};
	t_uint				i;

	i = 0;
	if (!(buffer = (t_intersec*)malloc(sizeof(t_intersec) * cam->w *
	((m == max) ? cam->h % max : cam->h / max))))
		error(1, 1, NULL);
	while (i < cam->w * ((m == max) ? cam->h % max : cam->h / max))
		buffer[i++] = def;
	env->cl.intersecs = create_buffer(&env->cl, CL_MEM_COPY_HOST_PTR,
	sizeof(t_intersec) * cam->w * ((m == max) ?
	cam->h % max : cam->h / max), buffer);
	free(buffer);
}
