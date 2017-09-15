/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_sphere.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchenaud <jchenaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/12 01:59:17 by jchenaud          #+#    #+#             */
/*   Updated: 2017/09/12 02:42:26 by jchenaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	pars_sphere_anex(xmlNode *current, t_obj *new_obj)
{
	if (ft_strcmp((char*)current->name, "pos") == 0)
		new_obj->pos = get_float3(current);
	else if (ft_strcmp((char*)current->name, "rot") == 0)
		new_obj->rot = get_float3(current);
	else if (ft_strcmp((char*)current->name, "hitbox") == 0)
		get_box(current, new_obj);
	else if (ft_strcmp((char*)current->name, "col") == 0)
		new_obj->mat.col = get_color(current);
	else if (ft_strcmp((char*)current->name, "rad") == 0)
		new_obj->obj.sphere.rad = get_rad(current);
	else if (ft_strcmp((char*)current->name, "ref") == 0)
		new_obj->mat.ref = get_float4(current);
	else if (ft_strcmp((char*)current->name, "refrac") == 0)
		new_obj->mat.refrac = get_float_xml("x", current);
	else if (ft_strcmp((char*)current->name, "texture") == 0)
		get_texture(current, new_obj);
	else
		exit(0);
}

int		pars_sphere(xmlNode *current, t_obj *new_obj)
{
	new_obj->type = SPHERE;
	if (!(current = current->children))
		return (-1);
	while (current != NULL)
	{
		if (current->type == XML_ELEMENT_NODE)
			pars_sphere_anex(current, new_obj);
		current = current->next;
	}
	return (0);
}
