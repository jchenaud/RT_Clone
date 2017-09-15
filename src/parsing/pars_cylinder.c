/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_cylinder.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchenaud <jchenaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/12 03:32:08 by jchenaud          #+#    #+#             */
/*   Updated: 2017/09/12 04:16:36 by jchenaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	pars_cylinder_anex2(xmlNode *current, t_obj *new_obj, int find)
{
	if (find == 1)
		return ;
	else if (ft_strcmp((char*)current->name, "norm") == 0)
		new_obj->obj.cylinder.norm = get_float3_normal(current);
	else if (ft_strcmp((char*)current->name, "!norm") == 0)
		new_obj->obj.cylinder.norm = get_float3(current);
	else if (ft_strcmp((char*)current->name, "rad") == 0)
		new_obj->obj.cylinder.rad = get_rad(current);
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

void	pars_cylinder_anex(xmlNode *current, t_obj *new_obj)
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
	pars_cylinder_anex2(current, new_obj, find);
}

int		pars_cylinder(xmlNode *current, t_obj *new_obj)
{
	new_obj->type = CYLINDER;
	if (!(current = current->children))
		return (-1);
	while (current != NULL)
	{
		if (current->type == XML_ELEMENT_NODE)
			pars_cylinder_anex(current, new_obj);
		current = current->next;
	}
	return (0);
}
