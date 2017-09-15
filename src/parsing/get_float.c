/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_float.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchenaud <jchenaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/12 23:58:41 by jchenaud          #+#    #+#             */
/*   Updated: 2017/09/13 00:16:45 by jchenaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

cl_float	get_float_xml(char *name, xmlNode *current)
{
	char		*data;
	cl_float	n;

	data = (char*)xmlGetProp(current, (const xmlChar*)name);
	if (!data)
		return (0.00);
	n = ft_atof(data);
	free(data);
	return (n);
}

cl_float3	get_float3(xmlNode *current)
{
	cl_float3 fl;

	fl.x = get_float_xml("x", current);
	fl.y = get_float_xml("y", current);
	fl.z = get_float_xml("z", current);
	return (fl);
}

cl_float3	get_float3_normal(xmlNode *current)
{
	cl_float3 fl;

	fl.x = get_float_xml("x", current);
	fl.y = get_float_xml("y", current);
	fl.z = get_float_xml("z", current);
	normalize_vec3(&fl);
	return (fl);
}

cl_float4	get_float4(xmlNode *current)
{
	cl_float3 fl;

	fl.x = get_float_xml("x", current);
	fl.y = get_float_xml("y", current);
	fl.z = get_float_xml("z", current);
	fl.w = get_float_xml("w", current);
	return (fl);
}
