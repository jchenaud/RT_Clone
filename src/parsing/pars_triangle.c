/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_triangle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchenaud <jchenaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/15 04:30:00 by jchenaud          #+#    #+#             */
/*   Updated: 2017/09/15 05:53:13 by jchenaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"


static void	pars_tr_anex3(xmlNode *current, t_obj *new_obj)
{
	if (ft_strcmp((char*)current->name, "norm_1") == 0)
	 	new_obj->obj.triangle.norm[0] = get_float3_normal(current);
	else if (ft_strcmp((char*)current->name, "norm_2") == 0)
	 	new_obj->obj.triangle.norm[1] = get_float3_normal(current);
	else if (ft_strcmp((char*)current->name, "norm_3") == 0)
	 	new_obj->obj.triangle.norm[2] = get_float3_normal(current);
	else if (ft_strcmp((char*)current->name, "!norm_1") == 0)
	 	new_obj->obj.triangle.norm[0] = get_float3(current);
	else if (ft_strcmp((char*)current->name, "!norm_2") == 0)
	 	new_obj->obj.triangle.norm[1] = get_float3(current);
	else if (ft_strcmp((char*)current->name, "!norm_3") == 0)
	 	new_obj->obj.triangle.norm[2] = get_float3(current);
}

static void	pars_tr_anex2(xmlNode *current, t_obj *new_obj)
{
	if (ft_strcmp((char*)current->name, "pos_1") == 0)
	 	new_obj->obj.triangle.point[0] = get_float3(current);
	else if (ft_strcmp((char*)current->name, "pos_2") == 0)
	 	new_obj->obj.triangle.point[1] = get_float3(current);
	else if (ft_strcmp((char*)current->name, "pos_3") == 0)
	 	new_obj->obj.triangle.point[2] = get_float3(current);
	else
		pars_tr_anex3(current,new_obj);
}


static void	pars_tr_anex(xmlNode *current, t_obj *new_obj)
{
	if (ft_strcmp((char*)current->name, "rot") == 0)
		new_obj->rot = get_float3(current);
	else if (ft_strcmp((char*)current->name, "col") == 0)
		new_obj->mat.col = get_color(current);
	else if (ft_strcmp((char*)current->name, "ref") == 0)
		new_obj->mat.ref = get_float4(current);
	else if (ft_strcmp((char*)current->name, "refrac") == 0)
		new_obj->mat.refrac = get_float_xml("x", current);
	else if (ft_strcmp((char*)current->name, "texture") == 0)
		get_texture(current, new_obj);
	else if (ft_strcmp((char*)current->name, "hitbox") == 0)
		get_box(current, new_obj);
	else 
		pars_tr_anex2(current,new_obj);
	// if (ft_strcmp((char*)current->name, "pos_1") == 0)
	// 	new_obj->obj.triagle.p = get_float3(current);

}


int		pars_triangle(xmlNode *current, t_obj *new_obj)
{
	new_obj->type = TRIANGLE;
	if (!(current = current->children))
		return (-1);
	while (current != NULL)
	{
		if (current->type == XML_ELEMENT_NODE)
			pars_tr_anex(current, new_obj);
		current = current->next;
	}
	return (0);


}