/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pars_prefab.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchenaud <jchenaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/06 01:53:33 by jchenaud          #+#    #+#             */
/*   Updated: 2017/09/29 13:43:49 by jchenaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libxml/xmlmemory.h"
#include "rt.h"

static int	pars_obj_pref_anex(xmlNode *current, t_obj *new_obj, t_env *e)
{
	if (ft_strcmp((char*)current->name, "cone") == 0)
	{
		if (pars_cone(current, new_obj) == -1)
			return (-1);
		ft_lstadd(&e->pref->p_obj, ft_lstnew(new_obj, sizeof(t_obj)));
	}
	else if (ft_strcmp((char*)current->name, "cylinder") == 0)
	{
		if (pars_cylinder(current, new_obj) == -1)
			return (-1);
		ft_lstadd(&e->pref->p_obj, ft_lstnew(new_obj, sizeof(t_obj)));
	}
	return (0);
}

static int	pars_obj_pref(xmlNode *current, t_obj *new_obj, t_env *e)
{
	if (ft_strcmp((char*)current->name, "sphere") == 0)
	{
		if (pars_sphere(current, new_obj) == -1)
			return (-1);
		ft_lstadd(&e->pref->p_obj, ft_lstnew(new_obj, sizeof(t_obj)));
	}
	else if (ft_strcmp((char*)current->name, "pave") == 0)
	{
		if (pars_pave(current, new_obj) == -1)
			return (-1);
		ft_lstadd(&e->pref->p_obj, ft_lstnew(new_obj, sizeof(t_obj)));
	}
	else if (ft_strcmp((char*)current->name, "plan") == 0)
	{
		if (pars_plan(current, new_obj) == -1)
			return (-1);
		ft_lstadd(&e->pref->p_obj, ft_lstnew(new_obj, sizeof(t_obj)));
	}
	else if (pars_obj_pref_anex(current, new_obj, e) == -1)
		return (-1);
	return (0);
}

int			ft_pars_prefab(t_env *e, xmlNode *current)
{
	t_obj	new_obj;
	t_list	*tmp_af;

	e->pref->p_obj = NULL;
	ft_bzero(&new_obj, sizeof(t_obj));
	ft_init_obj_default(&new_obj);
	tmp_af = e->pref->p_obj;
	if (ft_strcmp((char*)current->name, "prefab") != 0)
		return (-1);
	if (!(current = current->children))
		return (-1);
	if (!(current = current->next))
		return (-1);
	while (current != NULL)
	{
		if (current->type == XML_ELEMENT_NODE)
		{
			if (pars_obj_pref(current, &new_obj, e) == -1)
				return (-1);
		}
		current = current->next;
	}
	return (0);
}
