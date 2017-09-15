/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_other.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchenaud <jchenaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 01:58:30 by jchenaud          #+#    #+#             */
/*   Updated: 2017/09/13 02:02:32 by jchenaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_color		get_color(xmlNode *current)
{
	t_color col;

	col.r = get_uchar_xml("R", current);
	col.g = get_uchar_xml("B", current);
	col.b = get_uchar_xml("V", current);
	col.a = get_uchar_xml("T", current);
	return (col);
}

cl_float3	get_light_fac(xmlNode *current)
{
	cl_float3 i;

	i.x = get_float_xml("amb", current);
	i.y = get_float_xml("dif", current);
	i.z = get_float_xml("spec", current);
	return (i);
}

cl_float	get_rad(xmlNode *current)
{
	cl_float rad;

	rad = get_float_xml("rad", current);
	return (rad);
}

cl_float	get_ang(xmlNode *current)
{
	cl_float angle;

	angle = get_float_xml("angle", current);
	return (angle);
}
