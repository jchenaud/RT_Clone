/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat_x_vec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/13 12:46:07 by pribault          #+#    #+#             */
/*   Updated: 2017/08/22 16:50:03 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmath.h"

t_vec2	mat_2_vec(t_mat2 mat, t_vec2 vec)
{
	return (new_vec2(
	mat.x.x * vec.x + mat.x.y * vec.y,
	mat.y.x * vec.x + mat.y.y * vec.y));
}

t_vec3	mat_3_vec(t_mat3 mat, t_vec3 vec)
{
	return (new_vec3(
	mat.x.x * vec.x + mat.x.y * vec.y + mat.x.z * vec.z,
	mat.y.x * vec.x + mat.y.y * vec.y + mat.y.z * vec.z,
	mat.z.x * vec.x + mat.z.y * vec.y + mat.z.z * vec.z));
}

t_vec4	mat_4_vec(t_mat4 mat, t_vec4 vec)
{
	return (new_vec4(
	mat.x.x * vec.x + mat.x.y * vec.y + mat.x.z * vec.z + mat.x.w * vec.w,
	mat.y.x * vec.x + mat.y.y * vec.y + mat.y.z * vec.z + mat.y.w * vec.w,
	mat.z.x * vec.x + mat.z.y * vec.y + mat.z.z * vec.z + mat.z.w * vec.w,
	mat.w.x * vec.x + mat.w.y * vec.y + mat.w.z * vec.z + mat.w.w * vec.w));
}
