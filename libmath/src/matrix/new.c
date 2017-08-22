/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/13 11:02:11 by pribault          #+#    #+#             */
/*   Updated: 2017/08/22 16:50:06 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmath.h"

t_mat2	new_mat2(t_vec2 x, t_vec2 y)
{
	return ((t_mat2){x, y});
}

t_mat3	new_mat3(t_vec3 x, t_vec3 y, t_vec3 z)
{
	return ((t_mat3){x, y, z});
}

t_mat4	new_mat4(t_vec4 x, t_vec4 y, t_vec4 z, t_vec4 w)
{
	return ((t_mat4){x, y, z, w});
}
