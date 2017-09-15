/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_hitbox.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchenaud <jchenaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 00:39:20 by jchenaud          #+#    #+#             */
/*   Updated: 2017/09/13 06:04:46 by jchenaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	get_box_caract(xmlNode *current, t_obj *new_obj)
{
	if (ft_strcmp((char*)current->name, "rot") == 0)
		new_obj->hitbox.rot = get_float3(current);
	else if (ft_strcmp((char*)current->name, "min") == 0)
		new_obj->hitbox.min = get_float3(current);
	else if (ft_strcmp((char*)current->name, "max") == 0)
		new_obj->hitbox.max = get_float3(current);
}

void		get_box(xmlNode *current, t_obj *new_obj)
{
	char *data;

	if (!(data = (char*)xmlGetProp(current, (const xmlChar*)"type")))
		new_obj->hitbox.type = VISIBLE;
	else if (ft_strcmp((char*)data, "invisible") == 0)
		new_obj->hitbox.type = INVISIBLE;
	else
		new_obj->hitbox.type = VISIBLE;
	if (data)
		free(data);
	if (!(current = current->children))
		return ;
	while (current != NULL)
	{
		if (current->type == XML_ELEMENT_NODE)
			get_box_caract(current, new_obj);
		current = current->next;
	}
}
