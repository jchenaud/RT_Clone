/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prefab_modi.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchenaud <jchenaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/08 04:36:54 by jchenaud          #+#    #+#             */
/*   Updated: 2017/09/29 14:23:47 by jchenaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static t_prefab	*are_prefab(xmlNode *current, t_prefab *pref)
{
	t_prefab *tmp;

	tmp = pref;
	while (tmp != NULL && ft_strcmp((char*)current->name,
				tmp->prefab_name) != 0)
	{
		if (!(tmp = tmp->next))
			return (NULL);
	}
	return (tmp);
}

static int		ft_add_modi(xmlNode *current, t_prefab *tmp)
{
	if (!(current = current->children))
		return (-1);
	while (current != NULL)
	{
		if (current->type == XML_ELEMENT_NODE)
		{
			if (ft_strcmp((char*)current->name, "pos") == 0)
				modi_pos(tmp, current);
			else if (ft_strcmp((char*)current->name, "rot") == 0)
				modi_rot(tmp, current);
			else if (ft_strcmp((char*)current->name, "size") == 0)
				modi_size(tmp, current);
		}
		current = current->next;
	}
	return (0);
}

static void		ft_add_to_prefab(t_prefab *new_pref, t_env *e)
{
	t_prefab *tmp;

	tmp = e->pf_o;
	if (!e->pf_o)
	{
		e->pf_o = new_pref;
		e->pf_o->next = NULL;
	}
	else
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new_pref;
		tmp = tmp->next;
		tmp->next = NULL;
	}
}

static int		cp_prefab(t_prefab *tmp_pref, t_env *e, xmlNode *current)
{
	t_prefab *new_pref;

	new_pref = malloc(sizeof(t_prefab));
	ft_memcpy(new_pref, tmp_pref, sizeof(t_prefab));
	ft_add_to_prefab(new_pref, e);
	ft_add_modi(current, new_pref);
	return (0);
}

int				ft_add_modifier_to_prefab(t_env *e, xmlNode *current)
{
	t_prefab *tmp;

	if (!(tmp = are_prefab(current, e->pref)))
		return (0);
	cp_prefab(tmp, e, current);
	return (0);
}
