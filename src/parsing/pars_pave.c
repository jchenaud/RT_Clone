/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_pave.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchenaud <jchenaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/12 02:40:58 by jchenaud          #+#    #+#             */
/*   Updated: 2017/10/01 01:01:32 by jchenaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	pars_pave_anex(xmlNode *current, t_obj *new_obj)
{
	if (ft_strcmp((char*)current->name, "pos") == 0)
		new_obj->pos = get_float3(current);
	else if (ft_strcmp((char*)current->name, "rot") == 0)
		new_obj->rot = get_float3(current);
	else if (ft_strcmp((char*)current->name, "hitbox") == 0)
		get_box(current, new_obj);
	else if (ft_strcmp((char*)current->name, "col") == 0)
		new_obj->mat.col = get_color(current);
	else if (ft_strcmp((char*)current->name, "size") == 0)
		new_obj->obj.pave.size = get_float3(current);
	else if (ft_strcmp((char*)current->name, "ref") == 0)
		new_obj->mat.ref = get_float4(current);
	else if (ft_strcmp((char*)current->name, "refrac") == 0)
		new_obj->mat.refrac = get_float_xml("x", current);
	else if (ft_strcmp((char*)current->name, "texture") == 0)
		get_texture(current, new_obj);
	else
		ft_printf("Warning not valid Node on pave[%s]\n", current->name);
}

int		pars_pave(xmlNode *current, t_obj *new_obj)
{
	new_obj->type = PAVE;
	if (!(current = current->children))
		return (-1);
	while (current != NULL)
	{
		if (current->type == XML_ELEMENT_NODE)
			pars_pave_anex(current, new_obj);
		current = current->next;
	}
	return (0);
}
