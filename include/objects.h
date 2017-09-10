/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/20 19:05:42 by pribault          #+#    #+#             */
/*   Updated: 2017/09/06 05:02:10 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_H
# define OBJECTS_H

# include "libimages.h"

# ifdef __APPLE__
#  include <OpenCL/cl.h>
# endif
# ifdef __linux__
#  include <CL/cl.h>
# endif

/*
** # pragma pack(1)
*/

typedef struct			s_ray
{
	cl_float3			pos;
	cl_float3			dir;
	cl_float			f;
}						t_ray;

typedef struct			s_intersec
{
	cl_int				obj;
	cl_float			h;
}						t_intersec;

typedef struct			s_hitbox
{
	cl_uchar			type;
	cl_float3			rot;
	cl_float3			min;
	cl_float3			max;
	cl_float3			r_min;
	cl_float3			r_max;
}						t_hitbox;

typedef struct			s_sphere
{
	cl_float			rad;
}						t_sphere;

typedef struct			s_pave
{
	cl_float3			size;
}						t_pave;

typedef struct			s_plan
{
	cl_float3			norm;
}						t_plan;

typedef struct			s_cone
{
	cl_float3			norm;
	cl_float			angle;
}						t_cone;

typedef struct			s_cylinder
{
	cl_float3			norm;
	cl_float			rad;
}						t_cylinder;

typedef union			u_union
{
	t_pave				pave;
	t_sphere			sphere;
	t_plan				plan;
	t_cone				cone;
	t_cylinder			cylinder;
}						t_union;

typedef struct			s_cam
{
	cl_float3			pos;
	cl_float3			rot;
	cl_float3			dir;
	cl_float2			fov;
	cl_float			dis;
	cl_uint				w;
	cl_uint				h;
	t_img				*img;
	char				*output;
}						t_cam;

/*
**	i correspond to light intensity:
**	- i.x = ambient
**	- i.y = diffuse
**	- i.z = specular
*/

typedef struct			s_light
{
	cl_float3			pos;
	t_color				col;
	cl_float3			i;
}						t_light;

/*
**	for reflection vector:
**	- ref.x = ambient
**	- ref.y = diffuse
**	- ref.z = specular
*/

typedef struct			s_obj
{
	cl_float3			pos;
	cl_float3			rot;
	cl_uchar			type;
	t_color				col;
	cl_float4			ref;
	t_hitbox			hitbox;
	t_union				obj;
}						t_obj;

typedef struct			s_prefab
{
	char 				*prefab_name;
	cl_float3			pos;
	cl_float3			rot;
	t_list				*p_obj;
	struct s_prefab		*next;
}						t_prefab;

#endif
