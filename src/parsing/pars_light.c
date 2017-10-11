/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_light.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchenaud <jchenaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 02:29:19 by jchenaud          #+#    #+#             */
/*   Updated: 2017/10/01 01:00:37 by jchenaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

cl_uchar	get_light_type(xmlNode *current)
{
	cl_uchar	type;
	char		*data;

	if (!(data = (char*)xmlGetProp(current, (const xmlChar*)"parallele")))
	{
		type = 0;
		return (type);
	}
	type = PARALLELE;
	return (type);
}

static void	pars_light_anex(xmlNode *current, t_light *new_light)
{
	if (ft_strcmp((char*)current->name, "pos") == 0)
		new_light->pos = get_float3(current);
	else if (ft_strcmp((char*)current->name, "col") == 0)
		new_light->col = get_color(current);
	else if (ft_strcmp((char*)current->name, "i") == 0)
		new_light->i = get_light_fac(current);
	else if (ft_strcmp((char*)current->name, "type") == 0)
		new_light->type = get_light_type(current);
	else if (ft_strcmp((char*)current->name, "norm") == 0)
		new_light->norm = get_float3_normal(current);
	else
		ft_printf("Warning not valid Node on light[%s]\n", current->name);
}

int			pars_light(xmlNode *current, t_light *new_light)
{
	if (!(current = current->children))
		return (-1);
	while (current != NULL)
	{
		if (current->type == XML_ELEMENT_NODE)
			pars_light_anex(current, new_light);
		current = current->next;
	}
	return (0);
}
