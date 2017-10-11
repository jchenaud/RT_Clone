/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_pref.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchenaud <jchenaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/29 11:25:55 by jchenaud          #+#    #+#             */
/*   Updated: 2017/09/29 11:27:34 by jchenaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

char			*get_path_prefab(xmlNode *current)
{
	char *data;

	data = (char*)xmlGetProp(current, (const xmlChar*)"PATH");
	return (data);
}

char			*get_p_name(xmlNode *current, int i)
{
	char *data;
	char *num;

	num = (char*)malloc(sizeof(char) * 2);
	num[0] = (64 + i);
	num[1] = '\0';
	data = (char*)xmlGetProp(current, (const xmlChar*)num);
	free(num);
	return (data);
}
