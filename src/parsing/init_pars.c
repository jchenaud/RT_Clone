/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pars.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchenaud <jchenaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/29 15:44:09 by jchenaud          #+#    #+#             */
/*   Updated: 2017/10/01 02:06:47 by jchenaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_init_obj_default(t_obj *new_obj)
{
	new_obj->hitbox.min.x = -1000000.0;
	new_obj->hitbox.min.y = -1000000.0;
	new_obj->hitbox.min.z = -1000000.0;
	new_obj->hitbox.max.x = 1000000.0;
	new_obj->hitbox.max.y = 1000000.0;
	new_obj->hitbox.max.z = 1000000.0;
}

void	ft_init_cam(t_cam *new_cam)
{
	new_cam->w = 1280;
	new_cam->h = 720;
}

void	ft_bzero_init(t_obj *new_obj, t_cam *new_cam, t_light *new_light)
{
	ft_bzero(new_obj, sizeof(t_obj));
	ft_bzero(new_cam, sizeof(t_cam));
	ft_bzero(new_light, sizeof(t_light));
	ft_init_obj_default(new_obj);
}

xmlNode	*ft_initial_pars(xmlDoc **doc, xmlNode *root, t_env *e, char *file)
{
	e->pref = NULL;
	e->pf_o = NULL;
	*doc = xmlReadFile(file, NULL, 0);
	if (*doc == NULL)
		return (NULL);
	root = xmlDocGetRootElement(*doc);
	if (ft_strcmp((char*)root->name, "scene") != 0)
		return (NULL);
	if ((root = root->children))
	{
		if (!(root = root->next))
			return (NULL);
	}
	else
		return (NULL);
	if (ft_strcmp((char*)root->name, "Include") == 0)
	{
		if (ft_inc_prefab(root, e) == -1)
			return (NULL);
		root = root->next;
	}
	return (root);
}
