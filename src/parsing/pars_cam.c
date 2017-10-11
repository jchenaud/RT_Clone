/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_cam.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchenaud <jchenaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 02:05:05 by jchenaud          #+#    #+#             */
/*   Updated: 2017/10/01 01:18:35 by jchenaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	pars_cam_anex2(xmlNode *current, t_cam *new_cam, int find)
{
	if (find == 1)
		return ;
	else if (ft_strcmp((char*)current->name, "w") == 0)
		new_cam->w = get_w(current);
	else if (ft_strcmp((char*)current->name, "h") == 0)
		new_cam->h = get_h(current);
	else if (ft_strcmp((char*)current->name, "fov") == 0)
		new_cam->fov = get_fov(current);
	else if (ft_strcmp((char*)current->name, "dis") == 0)
		new_cam->dis = get_dis(current);
	else if (ft_strcmp((char*)current->name, "export") == 0)
	{
		new_cam->output = (char*)xmlGetProp(current,
			(const xmlChar*)"PATH");
	}
	else
		ft_printf("Warning not valid Node on cam [%s]\n", current->name);
}

static void	pars_cam_anex(xmlNode *current, t_cam *new_cam)
{
	int find;

	find = 0;
	if (ft_strcmp((char*)current->name, "pos") == 0)
	{
		new_cam->pos = get_float3(current);
		find = 1;
	}
	else if (ft_strcmp((char*)current->name, "dir") == 0)
	{
		new_cam->dir = get_float3(current);
		find = 1;
	}
	else if (ft_strcmp((char*)current->name, "rot") == 0)
	{
		new_cam->rot = get_float3(current);
		find = 1;
	}
	pars_cam_anex2(current, new_cam, find);
}

int			pars_cam(xmlNode *current, t_cam *new_cam)
{
	if (!(current = current->children))
		return (-1);
	ft_init_cam(new_cam);
	while (current != NULL)
	{
		if (current->type == XML_ELEMENT_NODE)
			pars_cam_anex(current, new_cam);
		current = current->next;
	}
	return (0);
}
