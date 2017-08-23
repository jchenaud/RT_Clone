/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_struct.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/23 13:15:57 by pribault          #+#    #+#             */
/*   Updated: 2017/08/23 14:24:24 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CL_STRUCT_H
# define CL_STRUCT_H

# include <OpenCL/cl.h>

typedef struct			s_cl
{
	cl_command_queue	queue;
	cl_context			context;
	cl_kernel			raytracer;
	cl_platform_id		platform;
	cl_device_id		device;
	t_uint				n_obj;
	t_obj				*obj;
	t_uint				n_cam;
	t_cam				*cam;
	t_uint				n_light;
	t_light				*light;
}						t_cl;

#endif
