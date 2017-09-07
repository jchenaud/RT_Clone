/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/06 07:58:40 by pribault          #+#    #+#             */
/*   Updated: 2017/09/07 04:51:15 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	set_args(t_cl *cl)
{
	cl_int	err;

	if ((err = clSetKernelArg(cl->intersection, 1, sizeof(cl_mem),
	&cl->intersecs)) != CL_SUCCESS)
		error(49, 1, &err);
	if ((err = clSetKernelArg(cl->intersection, 2, sizeof(cl_mem),
	&cl->rays)) != CL_SUCCESS)
		error(49, 1, &err);
	if ((err = clSetKernelArg(cl->intersection, 3, sizeof(cl_mem),
	&cl->n_obj_mem)) != CL_SUCCESS)
		error(49, 1, &err);
	if ((err = clSetKernelArg(cl->intersection, 4, sizeof(cl_mem),
	&cl->obj_mem)) != CL_SUCCESS)
		error(49, 1, &err);
	if ((err = clSetKernelArg(cl->intersection, 5, sizeof(cl_mem),
	&cl->n_light_mem)) != CL_SUCCESS)
		error(49, 1, &err);
	if ((err = clSetKernelArg(cl->intersection, 6, sizeof(cl_mem),
	&cl->light_mem)) != CL_SUCCESS)
		error(49, 1, &err);
}

void		*calculate_intersections(t_env *env, size_t n)
{
	cl_mem	intersecs;
	cl_int	err;
	void	*ret;

	if (!(ret = malloc(sizeof(t_intersec) * n)))
		error(1, 1, NULL);
	intersecs = clCreateBuffer(env->cl.context, CL_MEM_ALLOC_HOST_PTR,
	sizeof(t_intersec) * n, NULL, &err);
	if (err != CL_SUCCESS)
		error(48, 1, &err);
	if ((err = clSetKernelArg(env->cl.intersection, 0, sizeof(cl_mem),
	&intersecs)) != CL_SUCCESS)
		error(49, 1, &err);
	set_args(&env->cl);
	clEnqueueNDRangeKernel(env->cl.queue, env->cl.intersection, 1, NULL, &n,
	NULL, 0, NULL, NULL);
	if (clFinish(env->cl.queue) != CL_SUCCESS)
		error(52, 1, NULL);
	clEnqueueReadBuffer(env->cl.queue, intersecs, CL_TRUE, 0,
	sizeof(t_intersec) * n, ret, 0, NULL, NULL);
	if (clFinish(env->cl.queue) != CL_SUCCESS)
		error(52, 1, NULL);
	env->cl.intersecs = intersecs;
	return (ret);
}
