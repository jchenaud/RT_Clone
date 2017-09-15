/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/23 13:09:03 by pribault          #+#    #+#             */
/*   Updated: 2017/09/14 05:07:26 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	alloc_images(t_list *cam)
{
	t_cam	*current;

	while (cam)
	{
		current = (t_cam*)cam->content;
		current->img = new_img(current->w, current->h);
		cam = cam->next;
	}
}

cl_kernel	create_kernel(t_cl *cl, char *file, char *name)
{
	cl_program	program;
	cl_int		tmp;
	char		log[32768];
	char		*line;
	int			fd[2];

	if ((fd[0] = open(file, O_RDONLY)) == -1)
		return ((cl_kernel)0);
	ft_get_all_lines(fd[0], &line);
	program = clCreateProgramWithSource(cl->context, 1, (const char**)&line,
	NULL, NULL);
	tmp = clBuildProgram(program, 1, &cl->device, NULL, NULL, NULL);
	clGetProgramBuildInfo(program, cl->device, CL_PROGRAM_BUILD_LOG, 32768,
	log, NULL);
	if (tmp == CL_SUCCESS)
		fd[1] = (ft_strlen(log)) ? 208 : 154;
	else
		fd[1] = 124;
	ft_printf("\033[38;5;68m%s:\n\033[38;5;%dm%s\033[0m\n",
	file, fd[1], (ft_strlen(log)) ? log : "ok");
	free(line);
	close(fd[0]);
	return (clCreateKernel(program, name, NULL));
}

void		init_opencl(t_cl *cl)
{
	if (clGetPlatformIDs(1, &cl->platform, NULL) != CL_SUCCESS)
		return ;
	if (clGetDeviceIDs(cl->platform, cl->device_type, 1, &cl->device, NULL)
	!= CL_SUCCESS)
		return ;
	cl->context = clCreateContext(NULL, 1, &cl->device, NULL, NULL, NULL);
	cl->queue = clCreateCommandQueue(cl->context, cl->device, 0, NULL);
	clGetDeviceInfo(cl->device, CL_DEVICE_NAME,
	sizeof(cl->name), &cl->name, NULL);
	clGetDeviceInfo(cl->device, CL_DEVICE_GLOBAL_MEM_SIZE,
	sizeof(cl->mem_size), &cl->mem_size, NULL);
	ft_printf("device: %s\nmemory: %u%s\n", &cl->name,
	(!(cl->mem_size / 1073741824)) ? cl->mem_size / 1048576 :
	cl->mem_size / 1073741824, (!(cl->mem_size / 1073741824)) ? "Mo" : "Go");
	cl->intersection = create_kernel(cl, "kernel/intersection.cl",
	"intersection");
	cl->antialiasing = create_kernel(cl, "kernel/antialiasing.cl",
	"antialiasing");
	cl->preview = create_kernel(cl, "kernel/preview.cl", "raytracer");
	cl->cam_rays = create_kernel(cl, "kernel/cam_rays.cl", "cam_rays");
	cl->calc_rays = create_kernel(cl, "kernel/rays.cl", "calc_rays");
	cl->render_img = create_kernel(cl, "kernel/render_image.cl", "render_img");
}
