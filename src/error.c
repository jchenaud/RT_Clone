/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/22 17:18:47 by pribault          #+#    #+#             */
/*   Updated: 2017/10/20 15:07:06 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
**	this file is very explicite... 😓
**
**		please i don't want to let a comment noooooooo 😭
*/

void	print_usage(void)
{
	char	*usage;
	int		fd;

	if ((fd = open("usage.txt", O_RDONLY)) == -1)
		return ;
	ft_get_all_lines(fd, &usage);
	ft_putstr(usage);
	free(usage);
	close(fd);
}

void	error_3(int error, void *param)
{
	if (error == 64)
		ft_putstr("parsing error");
	else if (error == 23)
		ft_putstr("iterations need 1 argument");
	else if (error == 24)
		ft_putstr("angle need 1 argument: radians or degrees");
	else if (error == 53)
		ft_printf("error deleting buffer %d", *((cl_int*)param));
	else
		ft_putstr("unknown error");
	(void)param;
}

void	error_2(int error, void *param)
{
	if (error == 21)
		ft_putstr("device need 1 argument, cpu or gpu");
	else if (error == 22)
		ft_putstr("device can only be cpu or gpu");
	else if (error == 33)
		ft_putstr("cannot create mlx window");
	else if (error == 34)
		ft_putstr("cannot create mlx image");
	else if (error == 35)
		ft_putstr("computer to old, please buy one newer");
	else if (error == 48)
		ft_printf("openCL error creating buffer: code %d",
		*((t_uint*)param));
	else if (error == 49)
		ft_printf("openCL error setting arg: code %d",
		*((t_uint*)param));
	else if (error == 50)
		ft_putstr("raytracer need objects to raytrace");
	else if (error == 51)
		ft_putstr("raytracer need lights");
	else if (error == 52)
		ft_putstr("invalid command queue");
	else
		error_3(error, param);
}

void	error(int error, char state, void *param)
{
	ft_putstr("\033[38;5;160merror: ");
	if (error == 0)
		print_usage();
	else if (error == 1)
		ft_putstr("cannot allocate memory");
	else if (error == 2)
		ft_printf("cannot open %s", param);
	else if (error == 16)
		ft_printf("please, specify only one file <3 #%s", param);
	else if (error == 17)
		ft_printf("unknow parameter %s", param);
	else if (error == 18)
		ft_putstr("title need 1 argument");
	else if (error == 19)
		ft_putstr("size need 2 arguments");
	else if (error == 20)
		ft_putstr("antialias need 1 argument");
	else if (error == 32)
		ft_putstr("cannot init mlx");
	else
		error_2(error, param);
	ft_putstr("\033[0m\n");
	if (state)
		exit(1);
}
