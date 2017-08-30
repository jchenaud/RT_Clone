/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_struct.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/23 13:15:57 by pribault          #+#    #+#             */
/*   Updated: 2017/08/26 23:20:40 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CL_STRUCT_H
# define CL_STRUCT_H

# include <OpenCL/cl.h>

typedef struct			s_resize_buff
{
	cl_mem				img_dest;
	cl_mem				dest;
	cl_mem				img_src;
	cl_mem				src;
}						t_resize_buff;

typedef struct			s_cl
{
	cl_command_queue	queue;
	cl_context			context;
	cl_kernel			raytracer;
	cl_kernel			resize;
	cl_kernel			antialiasing;
	cl_platform_id		platform;
	cl_device_id		device;
	t_uint				n_obj;
	t_obj				*obj;
	t_uint				n_light;
	t_light				*light;
	cl_mem				img_mem;
	cl_mem				cam_mem;
	cl_mem				n_obj_mem;
	cl_mem				obj_mem;
	cl_mem				n_light_mem;
	cl_mem				light_mem;
	cl_int				error;
}						t_cl;

#endif