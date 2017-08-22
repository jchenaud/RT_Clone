/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perspective.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/13 15:02:26 by pribault          #+#    #+#             */
/*   Updated: 2017/08/22 16:50:08 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmath.h"

t_mat4	perspective(t_type fy, t_type a, t_type zn, t_type zf)
{
	t_mat4	ret;
	t_type	f;

	f = tan(fy / 2);
	// f = (f) ? 1 / f : 0;
	ret.x = new_vec4(1 / (f * a), 0, 0, 0);
	ret.y = new_vec4(0, 1 / f, 0, 0);
	ret.z = new_vec4(0, 0, -(zf + zn) / (zf - zn), -1);
	ret.w = new_vec4(0, 0, -(2 * zf * zn) / (zf - zn), 0);
	debug_mat4(&ret);
	return (ret);
}
