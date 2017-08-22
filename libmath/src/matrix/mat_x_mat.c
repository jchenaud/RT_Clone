/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat_x_mat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/13 12:23:25 by pribault          #+#    #+#             */
/*   Updated: 2017/08/22 16:50:00 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmath.h"

t_mat2			mat_2_mat(t_mat2 a, t_mat2 b)
{
	return (new_mat2(
	new_vec2(a.x.x * b.x.x + a.x.y * b.y.x,
	a.x.x * b.x.y + a.x.y * b.y.y),
	new_vec2(a.y.x * b.x.x + a.y.y * b.y.x,
	a.y.x * b.x.y + a.y.y * b.y.y)));
}

t_mat3			mat_3_mat(t_mat3 a, t_mat3 b)
{
	return (new_mat3(
	new_vec3(a.x.x * b.x.x + a.x.y * b.y.x + a.x.z * b.z.x,
	a.x.x * b.x.y + a.x.y * b.y.y + a.x.z * b.z.y,
	a.x.x * b.x.z + a.x.y * b.y.z + a.x.z * b.z.z),
	new_vec3(a.y.x * b.x.x + a.y.y * b.y.x + a.y.z * b.z.x,
	a.y.x * b.x.y + a.y.y * b.y.y + a.y.z * b.z.y,
	a.y.x * b.x.z + a.y.y * b.y.z + a.y.z * b.z.z),
	new_vec3(a.z.x * b.x.x + a.z.y * b.y.x + a.z.z * b.z.x,
	a.z.x * b.x.y + a.z.y * b.y.y + a.z.z * b.z.y,
	a.z.x * b.x.z + a.z.y * b.y.z + a.z.z * b.z.z)));
}

t_mat4			mat_4_mat(t_mat4 a, t_mat4 b)
{
	return (new_mat4(
	new_vec4(a.x.x * b.x.x + a.x.y * b.y.x + a.x.z * b.z.x + a.x.w * b.w.x,
	a.x.x * b.x.y + a.x.y * b.y.y + a.x.z * b.z.y + a.x.w * b.w.y,
	a.x.x * b.x.z + a.x.y * b.y.z + a.x.z * b.z.z + a.x.w * b.w.z,
	a.x.x * b.x.w + a.x.y * b.y.w + a.x.z * b.z.w + a.x.w * b.w.w),
	new_vec4(a.y.x * b.x.x + a.y.y * b.y.x + a.y.z * b.z.x + a.y.w * b.w.x,
	a.y.x * b.x.y + a.y.y * b.y.y + a.y.z * b.z.y + a.y.w * b.w.y,
	a.y.x * b.x.z + a.y.y * b.y.z + a.y.z * b.z.z + a.y.w * b.w.z,
	a.y.x * b.x.w + a.y.y * b.y.w + a.y.z * b.z.w + a.y.w * b.w.w),
	new_vec4(a.z.x * b.x.x + a.z.y * b.y.x + a.z.z * b.z.x + a.z.w * b.w.x,
	a.z.x * b.x.y + a.z.y * b.y.y + a.z.z * b.z.y + a.z.w * b.w.y,
	a.z.x * b.x.z + a.z.y * b.y.z + a.z.z * b.z.z + a.z.w * b.w.z,
	a.z.x * b.x.w + a.z.y * b.y.w + a.z.z * b.z.w + a.z.w * b.w.w),
	new_vec4(a.w.x * b.x.x + a.w.y * b.y.x + a.w.z * b.z.x + a.w.w * b.w.x,
	a.w.x * b.x.y + a.w.y * b.y.y + a.w.z * b.z.y + a.w.w * b.w.y,
	a.w.x * b.x.z + a.w.y * b.y.z + a.w.z * b.z.z + a.w.w * b.w.z,
	a.w.x * b.x.w + a.w.y * b.y.w + a.w.z * b.z.w + a.w.w * b.w.w)));
}
