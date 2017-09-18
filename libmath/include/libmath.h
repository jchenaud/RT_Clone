/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libmath.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/22 16:41:55 by pribault          #+#    #+#             */
/*   Updated: 2017/09/16 11:15:24 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBMATH_H
# define LIBMATH_H

# ifdef __APPLE__
#  include <OpenCL/cl.h>
# endif
# ifdef __linux__
#  include <CL/cl.h>
# endif

# include <math.h>
# include "libft.h"

typedef cl_float	t_type;

typedef cl_float2	t_vec2;
typedef cl_float3	t_vec3;
typedef cl_float4	t_vec4;

typedef struct	s_mat2
{
	t_vec2		x;
	t_vec2		y;
}				t_mat2;

typedef struct	s_mat3
{
	t_vec3		x;
	t_vec3		y;
	t_vec3		z;
}				t_mat3;

typedef struct	s_mat4
{
	t_vec4		x;
	t_vec4		y;
	t_vec4		z;
	t_vec4		w;
}				t_mat4;

t_vec2			new_vec2(t_type x, t_type y);
t_vec3			new_vec3(t_type x, t_type y, t_type z);
t_vec4			new_vec4(t_type x, t_type y, t_type z, t_type w);

void			normalize_vec2(t_vec2 *vec);
void			normalize_vec3(t_vec3 *vec);
void			normalize_vec4(t_vec4 *vec);

t_vec2			add_vec2(t_vec2 a, t_vec2 b);
t_vec3			add_vec3(t_vec3 a, t_vec3 b);
t_vec4			add_vec4(t_vec4 a, t_vec4 b);

t_vec2			sub_vec2(t_vec2 a, t_vec2 b);
t_vec3			sub_vec3(t_vec3 a, t_vec3 b);
t_vec4			sub_vec4(t_vec4 a, t_vec4 b);

t_vec2			mult_vec2(t_vec2 a, t_vec2 b);
t_vec3			mult_vec3(t_vec3 a, t_vec3 b);
t_vec4			mult_vec4(t_vec4 a, t_vec4 b);

t_type			scalar_vec2(t_vec2 a, t_vec2 b);
t_type			scalar_vec3(t_vec3 a, t_vec3 b);
t_type			scalar_vec4(t_vec4 a, t_vec4 b);

void			debug_vec2(t_vec2 *vec);
void			debug_vec3(t_vec3 *vec);
void			debug_vec4(t_vec4 *vec);

t_vec3			cross_vec3(t_vec3 a, t_vec3 b);

void			rotate_vec2(t_vec2 *vec, t_type angle);
void			rotate_vec3(t_vec3 *vec, t_vec3 angle);

t_mat2			new_mat2(t_vec2 x, t_vec2 y);
t_mat3			new_mat3(t_vec3 x, t_vec3 y, t_vec3 z);
t_mat4			new_mat4(t_vec4 x, t_vec4 y, t_vec4 z, t_vec4 w);

void			clean_mat2(t_mat2 *mat);
void			clean_mat3(t_mat3 *mat);
void			clean_mat4(t_mat4 *mat);

void			set_id_mat2(t_mat2 *mat, t_type id);
void			set_id_mat3(t_mat3 *mat, t_type id);
void			set_id_mat4(t_mat4 *mat, t_type id);

t_mat2			mat_2_mat(t_mat2 a, t_mat2 b);
t_mat3			mat_3_mat(t_mat3 a, t_mat3 b);
t_mat4			mat_4_mat(t_mat4 a, t_mat4 b);

t_vec2			mat_2_vec(t_mat2 mat, t_vec2 vec);
t_vec3			mat_3_vec(t_mat3 mat, t_vec3 vec);
t_vec4			mat_4_vec(t_mat4 mat, t_vec4 vec);

void			debug_mat2(t_mat2 *mat);
void			debug_mat3(t_mat3 *mat);
void			debug_mat4(t_mat4 *mat);

t_mat4			lookat(t_vec3 eye, t_vec3 center, t_vec3 up);
t_mat4			perspective(t_type fy, t_type a, t_type zn, t_type zf);

#endif
