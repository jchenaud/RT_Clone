/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cam.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchenaud <jchenaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 00:22:06 by jchenaud          #+#    #+#             */
/*   Updated: 2017/09/13 00:34:52 by jchenaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

cl_uint		get_w(xmlNode *current)
{
	cl_uint w;

	w = get_uint_xml("W", current);
	if ((int)w == 0)
		w = 1280;
	return (w);
}

cl_uint		get_h(xmlNode *current)
{
	cl_uint h;

	h = get_uint_xml("H", current);
	if ((int)h == 0)
		h = 720;
	return (h);
}

cl_float	get_dis(xmlNode *current)
{
	cl_float dis;

	dis = get_float_xml("dis", current);
	return (dis);
}

cl_float2	get_fov(xmlNode *current)
{
	cl_float2 fov;

	fov.x = get_float_xml("fov_x", current);
	fov.y = get_float_xml("fov_y", current);
	return (fov);
}
