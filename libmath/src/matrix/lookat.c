/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lookat.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/13 14:53:38 by pribault          #+#    #+#             */
/*   Updated: 2017/08/22 16:49:57 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmath.h"

t_mat4	lookat(t_vec3 eye, t_vec3 center, t_vec3 up)
{
	t_mat4	ret;
	t_vec3	f;
	t_vec3	s;
	t_vec3	u;

	f = sub_vec3(center, eye);
	normalize_vec3(&f);
	s = cross_vec3(f, up);
	normalize_vec3(&s);
	u = cross_vec3(s, f);
	ret.x = new_vec4(s.x, u.x, -f.x, 0);
	ret.y = new_vec4(s.y, u.y, -f.y, 0);
	ret.z = new_vec4(s.z, u.z, -f.z, 0);
	ret.w = new_vec4(-scalar_vec3(s, eye), -scalar_vec3(u, eye),
	scalar_vec3(f, eye), 1);
	debug_mat4(&ret);
	return (ret);
}
