/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 01:51:44 by jchenaud          #+#    #+#             */
/*   Updated: 2017/09/18 10:23:26 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	get_texture_size(xmlNode *current, t_obj *new_obj)
{
	new_obj->mat.size.x = get_float_xml("x", current);
	new_obj->mat.size.y = get_float_xml("y", current);
}

static void	get_texture_name(xmlNode *current, t_obj *new_obj, int i)
{
	char *data;

	if (!(data = (char*)xmlGetProp(current, (const xmlChar*)"src")))
		return ;
	new_obj->mat.textures[i].name = data;
}

void		get_texture(xmlNode *current, t_obj *new_obj)
{
	char *data;

	if (!(data = (char*)xmlGetProp(current, (const xmlChar*)"type")))
		return ;
	if (ft_strcmp((char*)data, "amb") == 0)
		get_texture_name(current, new_obj, 0);
	else if (ft_strcmp((char*)data, "dif") == 0)
		get_texture_name(current, new_obj, 1);
	else if (ft_strcmp((char*)data, "spec") == 0)
		get_texture_name(current, new_obj, 2);
	else if (ft_strcmp((char*)data, "normal") == 0)
		get_texture_name(current, new_obj, 3);
	else if (ft_strcmp((char*)data, "size") == 0)
		get_texture_size(current, new_obj);
	free(data);
}
