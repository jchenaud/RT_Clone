/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_cone.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchenaud <jchenaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/12 02:56:14 by jchenaud          #+#    #+#             */
/*   Updated: 2017/09/15 04:39:58 by jchenaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	pars_cone_anex2(xmlNode *current, t_obj *new_obj, int find)
{
	if (find == 1)
		return ;
	else if (ft_strcmp((char*)current->name, "norm") == 0)
		new_obj->obj.cylinder.norm = get_float3_normal(current);
	else if (ft_strcmp((char*)current->name, "!norm") == 0)
		new_obj->obj.cylinder.norm = get_float3(current);
	else if (ft_strcmp((char*)current->name, "angle") == 0)
		new_obj->obj.cone.angle = get_ang(current);
	else if (ft_strcmp((char*)current->name, "ref") == 0)
		new_obj->mat.ref = get_float4(current);
	else if (ft_strcmp((char*)current->name, "refrac") == 0)
		new_obj->mat.refrac = get_float_xml("x", current);
	else if (ft_strcmp((char*)current->name, "texture") == 0)
		get_texture(current, new_obj);
	else if (ft_strcmp((char*)current->name, "hitbox") == 0)
		get_box(current, new_obj);
	else
		exit(0);
}

static void	pars_cone_anex(xmlNode *current, t_obj *new_obj)
{
	int find;

	find = 0;
	if (ft_strcmp((char*)current->name, "pos") == 0)
	{
		new_obj->pos = get_float3(current);
		find = 1;
	}
	else if (ft_strcmp((char*)current->name, "rot") == 0)
	{
		new_obj->rot = get_float3(current);
		find = 1;
	}
	else if (ft_strcmp((char*)current->name, "col") == 0)
	{
		new_obj->mat.col = get_color(current);
		find = 1;
	}
	pars_cone_anex2(current, new_obj, find);
}

int		pars_cone(xmlNode *current, t_obj *new_obj)
{
	new_obj->type = CONE;
	if (!(current = current->children))
		return (-1);
	while (current != NULL)
	{
		if (current->type == XML_ELEMENT_NODE)
			pars_cone_anex(current, new_obj);
		current = current->next;
	}
	return (0);
}
