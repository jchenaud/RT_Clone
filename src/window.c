/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/23 13:09:03 by pribault          #+#    #+#             */
/*   Updated: 2017/08/23 13:22:11 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_img		*new_img(t_win *win, int w, int h)
{
	t_img	*new;
	int		bpp;
	int		size_l;
	int		endian;

	if (!(new = (t_img*)malloc(sizeof(t_img))))
		error(1, 1, NULL);
	new->w = w;
	new->h = h;
	if (!(new->ptr = mlx_new_image(win->mlx, w, h)))
		error(34, 1, NULL);
	if (!(new->img = (t_color*)mlx_get_data_addr(new->ptr, &bpp, &size_l,
	&endian)))
		error(34, 1, NULL);
	if (bpp != 32 || endian != 0)
		error(35, 1, NULL);
	ft_printf("bpp=%d endian=%d\n", bpp, endian);
	return (new);
}

cl_kernel	create_kernel(t_cl *cl, cl_device_id *device, char *file,
			char *name)
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
	tmp = clBuildProgram(program, 1, device, NULL, NULL, NULL);
	if (tmp != CL_SUCCESS)
	{
		ft_printf("\033[38;5;124mkernel error %d\n", tmp);
		clGetProgramBuildInfo(program, *device, CL_PROGRAM_BUILD_LOG, 4096,
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
	ft_printf("device: %s\n", name);
}

void		create_window(t_env *env, t_win *win)
{
	if (!(win->mlx = mlx_init()))
		error(32, 1, NULL);
	if (!(win->win = mlx_new_window(win->mlx, win->w, win->h, win->name)))
		error(33, 1, NULL);
	mlx_hook(win->win, 2, (1L << 0), (void*)&key_pressed, env);
	mlx_hook(win->win, 3, (1L << 1), (void*)&key_released, env);
	mlx_loop_hook(win->win, (void*)&loop, env);
}
