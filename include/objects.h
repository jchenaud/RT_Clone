/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/20 19:05:42 by pribault          #+#    #+#             */
/*   Updated: 2017/10/11 15:31:26 by pribault         ###   ########.fr       */
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

typedef union			u_name
{
	char				*name;
	int					n;
}						t_name;

typedef struct			s_texture
{
	char				*name;
	t_img				*img;
}						t_texture;

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

typedef struct			s_triangle
{
	cl_float3			point[3];
	cl_float3			norm[3];
}						t_triangle;

typedef union			u_union
{
	t_pave				pave;
	t_sphere			sphere;
	t_plan				plan;
	t_cone				cone;
	t_cylinder			cylinder;
	t_triangle			triangle;
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
	cl_float3			norm;
	cl_uchar			type;
}						t_light;

/*
**	for reflection vector:
**	- ref.x = ambient
**	- ref.y = diffuse
**	- ref.z = specular
*/

typedef struct			s_mat
{
	t_color				col;
	cl_float4			ref;
	cl_float			refrac;
	t_name				textures[4];
	cl_float2			size;
}						t_mat;

typedef struct			s_obj
{
	cl_float3			pos;
	cl_float3			rot;
	t_mat				mat;
	t_hitbox			hitbox;
	t_union				obj;
	cl_uchar			type;
}						t_obj;

typedef struct			s_prefab
{
	char				*prefab_name;
	cl_float3			pos;
	cl_float3			rot;
	t_list				*p_obj;
	struct s_prefab		*next;
}						t_prefab;

typedef struct			s_pref
{
	t_prefab			*tmp;
	xmlDoc				*doc;
	xmlNode				*current;
	char				*data;
	char				*p_name;
	char				*path;
	int					i;
	int					have_free_path;
}						t_pref;

#endif
