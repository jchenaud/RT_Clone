/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_anex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchenaud <jchenaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 06:05:13 by jchenaud          #+#    #+#             */
/*   Updated: 2017/09/13 06:21:46 by jchenaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

xmlNode		*ft_initial_pars(xmlDoc **doc, xmlNode *root, t_env *e, char *file)
{
	e->pref = NULL;
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