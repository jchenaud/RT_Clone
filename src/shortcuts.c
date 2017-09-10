/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shortcuts.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/07 01:17:12 by pribault          #+#    #+#             */
/*   Updated: 2017/09/10 03:10:43 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

cl_mem	create_buffer(t_cl *cl, cl_mem_flags flags, size_t size, void *ptr)
{
	cl_mem	new;

	new = clCreateBuffer(cl->context, flags,
	size, ptr, &cl->error);
	if (cl->error != CL_SUCCESS)
		error(48, 1, &cl->error);
	return (new);
}

void	set_kernel_arg(cl_kernel *kernel, cl_mem *mem, cl_uint i)
{
	cl_int	err;

	if ((err = clSetKernelArg(*kernel, i, sizeof(cl_mem),
	mem)) != CL_SUCCESS)
		error(49, 1, &err);
}

void	nd_range_kernel(t_cl *cl, cl_kernel *kernel, size_t n)
{
	clEnqueueNDRangeKernel(cl->queue, *kernel, 1, NULL, &n,
	NULL, 0, NULL, NULL);
	if (clFinish(cl->queue) != CL_SUCCESS)
		error(52, 1, NULL);
}

void	read_buffer(t_cl *cl, cl_mem mem, void *ptr, size_t size)
{
	clEnqueueReadBuffer(cl->queue, mem, CL_TRUE, 0,
	size, ptr, 0, NULL, NULL);
	if (clFinish(cl->queue) != CL_SUCCESS)
		error(52, 1, NULL);
}

void	delete_buffer(cl_mem mem)
{
	cl_int	err;

	if ((err = clReleaseMemObject(mem)) != CL_SUCCESS)
		error(53, 1, &err);
}
