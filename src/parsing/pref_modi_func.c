/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pref_modi_func.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchenaud <jchenaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/29 14:21:32 by jchenaud          #+#    #+#             */
/*   Updated: 2017/09/29 15:37:34 by jchenaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		modi_pos(t_prefab *tmp, xmlNode *current)
{
	t_list *tl;

	tl = tmp->p_obj;
	while (tl)
	{
		((t_obj*)tl->content)->pos.x += get_float_xml("x", current);
		((t_obj*)tl->content)->hitbox.min.x += get_float_xml("x", current);
		((t_obj*)tl->content)->hitbox.max.x += get_float_xml("x", current);
		((t_obj*)tl->content)->pos.y += get_float_xml("y", current);
		((t_obj*)tl->content)->hitbox.min.y += get_float_xml("y", current);
		((t_obj*)tl->content)->hitbox.max.y += get_float_xml("y", current);
		((t_obj*)tl->content)->pos.z += get_float_xml("z", current);
		((t_obj*)tl->content)->hitbox.min.z += get_float_xml("z", current);
		((t_obj*)tl->content)->hitbox.max.z += get_float_xml("z", current);
		tl = tl->next;
	}
}

void		modi_rot(t_prefab *tmp, xmlNode *current)
{
	t_list *tl;

	tl = (t_list*)tmp->p_obj;
	while (tl)
	{
		((t_obj*)tl->content)->rot.x += get_float_xml("x", current);
		((t_obj*)tl->content)->hitbox.rot.x += get_float_xml("x", current);
		((t_obj*)tl->content)->rot.y += get_float_xml("y", current);
		((t_obj*)tl->content)->hitbox.rot.y += get_float_xml("y", current);
		((t_obj*)tl->content)->rot.z += get_float_xml("z", current);
		((t_obj*)tl->content)->hitbox.rot.z += get_float_xml("z", current);
		tl = tl->next;
	}
}

void		modi_size(t_prefab *tmp, xmlNode *current)
{
	t_list *tl;

	tl = (t_list*)tmp->p_obj;
	if (((t_obj*)tl->content)->type == SPHERE)
		GET_SPHERE((*(t_obj*)tl->content)).rad *= get_float_xml("x", current);
	else if (((t_obj*)tl->content)->type == CYLINDER)
		GET_CYLINDER((*(t_obj*)tl->content)).rad *= get_float_xml("x", current);
	else if (((t_obj*)tl->content)->type == CONE)
		GET_CONE((*(t_obj*)tl->content)).angle *= get_float_xml("x", current);
	else if (((t_obj*)tl->content)->type == PAVE)
	{
		GET_PAVE((*(t_obj*)tl->content)).size.x *= get_float_xml("x", current);
		GET_PAVE((*(t_obj*)tl->content)).size.x *= get_float_xml("y", current);
		GET_PAVE((*(t_obj*)tl->content)).size.x *= get_float_xml("z", current);
	}
}
