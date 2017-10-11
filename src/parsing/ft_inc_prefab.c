/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_inc_prefab.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchenaud <jchenaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/06 01:51:45 by jchenaud          #+#    #+#             */
/*   Updated: 2017/09/29 11:30:34 by jchenaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libxml/xmlmemory.h"
#include "rt.h"

static int		number_of_prefab(xmlNode *current)
{
	char	*num;
	char	*data;
	int		n;

	num = (char*)malloc(sizeof(char) * 2);
	num[1] = '\0';
	n = 0;
	while (n < 26)
	{
		num[0] = (65 + n);
		data = (char*)xmlGetProp(current, (const xmlChar*)num);
		if (!data)
		{
			free(data);
			free(num);
			return (n);
		}
		n++;
		free(data);
	}
	free(data);
	free(num);
	return (26);
}

static void		ft_newprefab(t_env *e)
{
	t_prefab *tmp;

	tmp = e->pref;
	if (!e->pref)
	{
		e->pref = (t_prefab*)malloc(sizeof(t_prefab));
		e->pref->next = NULL;
	}
	else
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = (t_prefab*)malloc(sizeof(t_prefab));
		tmp = tmp->next;
		e->pref = tmp;
		e->pref->next = NULL;
	}
}

static void		ft_init_struct(t_pref *p, xmlNode *root)
{
	ft_bzero(p, sizeof(t_pref));
	p->i = 1;
	if (!(p->path = get_path_prefab(root)))
		p->path = "prefab";
	else
		p->have_free_path = 1;
}

static int		find_and_load(t_pref *p, xmlNode *root, t_env *e)
{
	if (p->i == 1)
		p->tmp = e->pref;
	p->p_name = get_p_name(root, p->i);
	e->pref->prefab_name = p->p_name;
	p->data = ft_joinf("%s/%s.xml", p->path, p->p_name);
	if (!(p->doc = xmlReadFile(p->data, NULL, 0)))
		return (-1);
	free(p->data);
	p->current = xmlDocGetRootElement(p->doc);
	return (0);
}

int				ft_inc_prefab(xmlNode *root, t_env *e)
{
	t_pref *p;

	if (!(p = malloc(sizeof(t_pref))))
		return (-1);
	ft_init_struct(p, root);
	while (p->i <= number_of_prefab(root))
	{
		ft_newprefab(e);
		if (find_and_load(p, root, e) == -1)
			return (-1);
		if (ft_pars_prefab(e, p->current) == -1)
			return (-1);
		xmlFreeDoc(p->doc);
		xmlCleanupParser();
		p->i++;
	}
	e->pref = p->tmp;
	if (p->have_free_path == 1)
		free(p->path);
	free(p);
	return (0);
}
