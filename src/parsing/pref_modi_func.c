/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pref_modi_func.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchenaud <jchenaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/29 14:21:32 by jchenaud          #+#    #+#             */
/*   Updated: 2017/10/21 13:57:03 by jchenaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			modi_pos(t_prefab *tmp, xmlNode *current)
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

t_vec3			ft_centeur(t_prefab *tmp)
{
	t_vec3	c;
	int		m;
	t_list	*tl;

	m = 0;
	tl = (t_list*)tmp->p_obj;
	while (tl)
	{
		c.x += ((t_obj*)tl->content)->pos.x;
		c.y += ((t_obj*)tl->content)->pos.y;
		c.z += ((t_obj*)tl->content)->pos.z;
		tl = tl->next;
		m++;
	}
	if (m != 0)
	{
		c.x = c.x / m;
		c.y = c.y / m;
		c.z = c.z / m;
	}
	return (c);
}

static void		modi_rot_anex(t_list *tl, t_vec3 angle, t_vec3 c)
{
	t_vec3 dif;

	dif = ((t_obj*)tl->content)->pos;
	((t_obj*)tl->content)->pos = sub_vec3(((t_obj*)tl->content)->pos, c);
	rotate_vec3(&((t_obj*)tl->content)->pos, angle);
	((t_obj*)tl->content)->pos = add_vec3(((t_obj*)tl->content)->pos, c);
	((t_obj*)tl->content)->rot = add_vec3(
		((t_obj*)tl->content)->rot, angle);
	dif = sub_vec3(((t_obj*)tl->content)->pos, dif);
	((t_obj*)tl->content)->hitbox.min = add_vec3(
		dif, ((t_obj*)tl->content)->hitbox.min);
	((t_obj*)tl->content)->hitbox.max = add_vec3(
		dif, ((t_obj*)tl->content)->hitbox.max);
	((t_obj*)tl->content)->hitbox.r_min = add_vec3(
		dif, ((t_obj*)tl->content)->hitbox.r_min);
	((t_obj*)tl->content)->hitbox.r_max = add_vec3(
		dif, ((t_obj*)tl->content)->hitbox.r_max);
	((t_obj*)tl->content)->hitbox.rot = add_vec3(
		((t_obj*)tl->content)->hitbox.rot, angle);
}

void			modi_rot(t_prefab *tmp, xmlNode *current)
{
	t_list *tl;
	t_vec3 angle;
	t_vec3 c;

	c = ft_centeur(tmp);
	angle.x = get_float_xml("x", current);
	angle.y = get_float_xml("y", current);
	angle.z = get_float_xml("z", current);
	tl = (t_list*)tmp->p_obj;
	while (tl)
	{
		modi_rot_anex(tl, angle, c);
		tl = tl->next;
	}
}

void			modi_size(t_prefab *tmp, xmlNode *current)
{
	t_list *tl;

	tl = (t_list*)tmp->p_obj;
	while (tl)
	{
		if (((t_obj*)tl->content)->type == SPHERE)
			GET_SPHERE((*(t_obj*)tl->content)).rad *= get_float_xml(
				"x", current);
		else if (((t_obj*)tl->content)->type == CYLINDER)
			GET_CYLINDER((*(t_obj*)tl->content)).rad *= get_float_xml(
				"x", current);
		else if (((t_obj*)tl->content)->type == CONE)
			GET_CONE((*(t_obj*)tl->content)).angle *= get_float_xml(
				"x", current);
		modi_size_hitbox(tl, current);
		tl = tl->next;
	}
}
