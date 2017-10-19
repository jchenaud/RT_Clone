/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_u_char_int.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchenaud <jchenaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 01:45:02 by jchenaud          #+#    #+#             */
/*   Updated: 2017/09/13 01:48:30 by jchenaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

cl_uchar	get_uchar_xml(char *name, xmlNode *current)
{
	char		*data;
	cl_uchar	c;

	data = (char*)xmlGetProp(current, (const xmlChar*)name);
	if (!data)
		return (0);
	c = ft_atou(data);
	free(data);
	return (c);
}

cl_uint		get_uint_xml(char *name, xmlNode *current)
{
	char		*data;
	cl_uint		i;

	data = (char*)xmlGetProp(current, (const xmlChar*)name);
	if (!data)
		return (0);
	i = ft_atou(data);
	free(data);
	return (i);
}
