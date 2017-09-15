/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_inc_prefab.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchenaud <jchenaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/06 01:51:45 by jchenaud          #+#    #+#             */
/*   Updated: 2017/09/14 01:56:39 by jchenaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libxml/xmlmemory.h"
#include "rt.h"

	
char *get_path_prefab(xmlNode *current)
{
	char  *data;

	data = (char*)xmlGetProp(current,(const xmlChar*)"PATH");
   	return (data);
}

char* get_p_name(xmlNode *current,int i)
{
	char  *data;
	char *num;
	num = (char*)malloc(sizeof(char)*2);
	num[0] = (64 + i);
	num[1] = '\0';

	data = (char*)xmlGetProp(current,(const xmlChar*)num);
	free(num);
   	return (data);

}


int  number_of_prefab(xmlNode *current)
{
	
   char  *num;
   char  *data;
   int  n;

	num = (char*)malloc(sizeof(char)*2);
   num[1] = '\0';
   n = 0;
	while (n < 26)
	{
		num[0] = (65 + n);
 	  	data = (char*)xmlGetProp(current,(const xmlChar*)num);
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
	return(26);
}


void ft_newprefab(t_env *e)
{
	t_prefab *tmp;
	tmp = e->pref;
	if (!e->pref)
	{
		e->pref =  (t_prefab*)malloc(sizeof(t_prefab));
		e->pref->next = NULL;
	}
	else
	{
		while (tmp->next != NULL)
			tmp = tmp->next;

		tmp->next = (t_prefab*)malloc(sizeof(t_prefab));
		tmp = tmp->next;
		//tmp->next  = NULL;
		e->pref = tmp;
		e->pref->next = NULL;
		}
}


int ft_inc_prefab(xmlNode* root, t_env *e)
{
	t_prefab *tmp;
	xmlDoc *doc;
	xmlNode *current;
	char *data;
	char *p_name;
	char *path;
	int i;
	int have_free_path;

	i = 1;
	have_free_path = 0;
	


	if (!(path = get_path_prefab(root)))
		path = "prefab";
	else 
		have_free_path = 1;

	while (i <= number_of_prefab(root))
	{

		ft_newprefab(e);
		if (i == 1)
			tmp = e->pref;

		p_name = get_p_name(root,i);
		e->pref->prefab_name = p_name;
	
	data = ft_joinf("%s/%s.xml",path,p_name);
	if(!(doc = xmlReadFile( data,NULL,0)))
		return (-1);  		
	free(data);
	current = xmlDocGetRootElement( doc );

		if (ft_pars_prefab(e,current) == -1)
			return(-1);

		xmlFreeDoc(doc);
		xmlCleanupParser();
		i++;
	}
	e->pref = tmp;

	if (have_free_path == 1)
 		free(path);
 	return(0);

}
