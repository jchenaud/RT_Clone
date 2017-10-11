/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchenaud <jchenaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/21 16:08:40 by jchenaud          #+#    #+#             */
/*   Updated: 2017/10/01 01:11:27 by jchenaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int	pars_obj2(xmlNode *current, t_obj new_obj, t_env *e)
{
	if (ft_strcmp((char*)current->name, "cone") == 0)
	{
		if (pars_cone(current, &new_obj) == -1)
			return (-1);
		ft_lstadd(&e->obj, ft_lstnew(&new_obj, sizeof(t_obj)));
	}
	else if (ft_strcmp((char*)current->name, "cylinder") == 0)
	{
		if (pars_cylinder(current, &new_obj) == -1)
			return (-1);
		ft_lstadd(&e->obj, ft_lstnew(&new_obj, sizeof(t_obj)));
	}
	else if (ft_strcmp((char*)current->name, "triangle") == 0)
	{
		if (pars_triangle(current, &new_obj) == -1)
			return (-1);
		ft_lstadd(&e->obj, ft_lstnew(&new_obj, sizeof(t_obj)));
	}
	else if (e->pref != NULL)
		ft_add_modifier_to_prefab(e, current);
	return (0);
}

static int	pars_obj(xmlNode *current, t_obj new_obj, t_env *e)
{
	if (ft_strcmp((char*)current->name, "sphere") == 0)
	{
		if (pars_sphere(current, &new_obj) == -1)
			return (-1);
		ft_lstadd(&e->obj, ft_lstnew(&new_obj, sizeof(t_obj)));
	}
	else if (ft_strcmp((char*)current->name, "pave") == 0)
	{
		if (pars_pave(current, &new_obj) == -1)
			return (-1);
		ft_lstadd(&e->obj, ft_lstnew(&new_obj, sizeof(t_obj)));
	}
	else if (ft_strcmp((char*)current->name, "plan") == 0)
	{
		if (pars_plan(current, &new_obj) == -1)
			return (-1);
		ft_lstadd(&e->obj, ft_lstnew(&new_obj, sizeof(t_obj)));
	}
	else
	{
		if (pars_obj2(current, new_obj, e) == -1)
			return (-1);
	}
	return (0);
}

static int	pars_cam_light(xmlNode *current, t_cam cam, t_light light, t_env *e)
{
	e->find_cam_light = 0;
	if (ft_strcmp((char*)current->name, "cam") == 0)
	{
		if (pars_cam(current, &cam) == -1)
			return (-1);
		ft_lstadd(&e->cam, ft_lstnew(&cam, sizeof(t_cam)));
		e->find_cam_light = 1;
		return (1);
	}
	else if (ft_strcmp((char*)current->name, "light") == 0)
	{
		if (pars_light(current, &light) == -1)
			return (-1);
		ft_lstadd(&e->light, ft_lstnew(&light, sizeof(t_light)));
		e->find_cam_light = 1;
		return (1);
	}
	return (0);
}

int			pars_content(xmlNode *root, t_env *e)
{
	t_obj	new_obj;
	t_cam	new_cam;
	t_light	new_light;
	xmlNode *current;

	current = root;
	while (current != NULL)
	{
		if (current->type == XML_ELEMENT_NODE)
		{
			ft_bzero_init(&new_obj, &new_cam, &new_light);
			if (pars_cam_light(current, new_cam, new_light, e) == -1)
				return (-1);
			else if (e->find_cam_light == 0)
			{
				if (pars_obj(current, new_obj, e) == -1)
					return (-1);
			}
		}
		current = current->next;
	}
	return (0);
}

int			parsing(char *file, t_env *e)
{
	xmlDoc	*doc;
	xmlNode	*root;

	root = NULL;
	if (!(root = ft_initial_pars(&doc, root, e, file)))
		return (-1);
	if (pars_content(root, e) == -1)
		return (-1);
	xmlFreeDoc(doc);
	xmlCleanupParser();
	ft_printf("\n");
	return (0);
}
