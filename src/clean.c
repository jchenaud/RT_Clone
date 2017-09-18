/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 10:36:23 by pribault          #+#    #+#             */
/*   Updated: 2017/09/18 10:51:40 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	convert_to_radians(t_obj *obj, t_uint n)
{
	t_uint	i;

	i = 0;
	while (i < n)
	{
		obj[i].rot.x *= ((2 * PI) / (float)360);
		obj[i].rot.y *= ((2 * PI) / (float)360);
		obj[i].rot.z *= ((2 * PI) / (float)360);
		i++;
	}
}

void	convert_rotations_to_normals(t_obj *obj, t_uint n)
{
	t_uint	i;

	i = 0;
	while (i < n)
	{
		if (obj[i].type == CONE)
			rotate_vec3(&obj[i].obj.cone.norm, obj[i].rot);
		else if (obj[i].type == CYLINDER)
			rotate_vec3(&obj[i].obj.cylinder.norm, obj[i].rot);
		else if (obj[i].type == PLAN)
			rotate_vec3(&obj[i].obj.plan.norm, obj[i].rot);
		i++;
	}
}
