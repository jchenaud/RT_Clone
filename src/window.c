/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/23 13:09:03 by pribault          #+#    #+#             */
/*   Updated: 2017/09/05 08:47:10 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

cl_kernel	create_kernel(t_cl *cl, char *file, char *name)
{
	cl_program	program;
	cl_int		tmp;
	char		log[4096];
	char		*line;
	int			fd;

	if ((fd = open(file, O_RDONLY)) == -1)
		return ((cl_kernel)0);
	ft_get_all_lines(fd, &line);
	program = clCreateProgramWithSource(cl->context, 1, (const char**)&line,
	NULL, NULL);
	tmp = clBuildProgram(program, 1, &cl->device, NULL, NULL, NULL);
	if (tmp != CL_SUCCESS)
	{
		ft_printf("\033[38;5;124m%s, kernel error %d\n", file, tmp);
		clGetProgramBuildInfo(program, cl->device, CL_PROGRAM_BUILD_LOG, 4096,
		log, NULL);
		ft_printf("log: %s\n\033[0m", log);
	}
	free(line);
	close(fd);
	return (clCreateKernel(program, name, NULL));
}

void		init_opencl(t_cl *cl)
{
	char			name[128];

	if (clGetPlatformIDs(1, &cl->platform, NULL) != CL_SUCCESS)
		return ;
	if (clGetDeviceIDs(cl->platform, CL_DEVICE_TYPE_GPU, 1, &cl->device, NULL)
	!= CL_SUCCESS)
		return ;
	cl->context = clCreateContext(NULL, 1, &cl->device, NULL, NULL, NULL);
	cl->queue = clCreateCommandQueue(cl->context, cl->device, 0, NULL);
	clGetDeviceInfo(cl->device, CL_DEVICE_NAME, 128, name, NULL);
	cl->raytracer = create_kernel(cl, "kernel/raytracer.cl", "raytracer");
	cl->resize = create_kernel(cl, "kernel/resize.cl", "resize");
	cl->antialiasing = create_kernel(cl, "kernel/antialiasing.cl",
	"antialiasing");
	cl->preview = create_kernel(cl, "kernel/preview.cl", "raytracer");
	ft_printf("device: %s\n", name);
}
