/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shortcuts.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/07 01:17:12 by pribault          #+#    #+#             */
/*   Updated: 2017/10/20 15:24:40 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
**	those functions are used to protect opencl functions,
**	if one fail the program quit, image cannot be calculated
*/

/*
**	create buffer in gpu memory
*/

cl_mem	create_buffer(t_cl *cl, cl_mem_flags flags, size_t size, void *ptr)
{
	cl_mem	new;

	new = clCreateBuffer(cl->context, flags,
	size, ptr, &cl->error);
	if (cl->error != CL_SUCCESS)
		error(48, 1, &cl->error);
	return (new);
}

/*
**	set wich arg is the buffer for the kernel
*/

void	set_kernel_arg(cl_kernel *kernel, cl_mem *mem, cl_uint i)
{
	cl_int	err;

	if ((err = clSetKernelArg(*kernel, i, sizeof(cl_mem),
	mem)) != CL_SUCCESS)
		error(49, 1, &err);
}

/*
**	launch a kernel and wait until finish
*/

void	nd_range_kernel(t_cl *cl, cl_kernel *kernel, size_t n)
{
	clEnqueueNDRangeKernel(cl->queue, *kernel, 1, NULL, &n,
	NULL, 0, NULL, NULL);
	if (clFinish(cl->queue) != CL_SUCCESS)
		error(52, 1, NULL);
}

/*
**	copy a buffer into a pointer
*/

void	read_buffer(t_cl *cl, cl_mem mem, void *ptr, size_t size)
{
	clEnqueueReadBuffer(cl->queue, mem, CL_TRUE, 0,
	size, ptr, 0, NULL, NULL);
	if (clFinish(cl->queue) != CL_SUCCESS)
		error(52, 1, NULL);
}

/*
**	release a buffer
*/

void	delete_buffer(cl_mem mem)
{
	cl_int	err;

	if ((err = clReleaseMemObject(mem)) != CL_SUCCESS)
		error(53, 1, &err);
}
