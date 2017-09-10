/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prefab_modi.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchenaud <jchenaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/08 04:36:54 by jchenaud          #+#    #+#             */
/*   Updated: 2017/09/10 04:32:11 by jchenaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_prefab *are_prefab(xmlNode* current,t_prefab *pref)
{
	 t_prefab *tmp;
	 tmp = pref;
	while ( tmp != NULL && ft_strcmp((char*)current->name,tmp->prefab_name) != 0 )//tmp->prefab_name != current->name )
	{
		if(!(tmp = tmp->next))
	 		return(NULL);
	 }
	return (tmp);
}

void  modi_pos(t_prefab *tmp, xmlNode *current)
{
	t_list *tmp_list;
	tmp_list = tmp->p_obj;
	while(tmp_list)
	{
		((t_obj*)tmp_list->content)->pos.x += get_float_xml("x",current);
		((t_obj*)tmp_list->content)->pos.y += get_float_xml("y",current);
		((t_obj*)tmp_list->content)->pos.z += get_float_xml("z",current);
		tmp_list = tmp_list->next;
	}
	
}


void modi_rot(t_prefab *tmp, xmlNode *current)
{
	t_list *tmp_list;
	tmp_list = (t_list*)tmp->p_obj;
	while(tmp_list)
	{
		((t_obj*)tmp_list->content)->rot.x += get_float_xml("x",current);
		((t_obj*)tmp_list->content)->rot.y += get_float_xml("y",current);
		((t_obj*)tmp_list->content)->rot.z += get_float_xml("z",current);
		tmp_list = tmp_list->next;
	}

}

void modi_size(t_prefab* tmp, xmlNode *current)
{
	t_list *tmp_list;
	tmp_list = (t_list*)tmp->p_obj;

	if(((t_obj*)tmp_list->content)->type == SPHERE)
		GET_SPHERE((*(t_obj*)tmp_list->content)).rad *= get_float_xml("x",current);
	else if (((t_obj*)tmp_list->content)->type == CYLINDER)
		GET_CYLINDER((*(t_obj*)tmp_list->content)).rad *= get_float_xml("x",current);
	else if (((t_obj*)tmp_list->content)->type == CONE)
		GET_CONE((*(t_obj*)tmp_list->content)).angle *= get_float_xml("x",current);
	else if (((t_obj*)tmp_list->content)->type == PAVE)
	{
		GET_PAVE((*(t_obj*)tmp_list->content)).size.x *= get_float_xml("x",current);
		GET_PAVE((*(t_obj*)tmp_list->content)).size.x *= get_float_xml("y",current);
		GET_PAVE((*(t_obj*)tmp_list->content)).size.x *= get_float_xml("z",current);
	}


}

int  ft_add_modi(xmlNode* current,t_prefab *tmp)
{
	if (!(current = current->children))
		return(-1);
	while (current != NULL)
  	{ 
  		if (current->type==XML_ELEMENT_NODE ) // sert a quoi
     	{
 
     		if(ft_strcmp((char*)current->name,"pos")== 0)
    			 modi_pos(tmp,current);
    		else if (ft_strcmp((char*)current->name,"rot") == 0)
  				modi_rot(tmp,current);
  			else if (ft_strcmp((char*)current->name,"size") == 0)
  				modi_size(tmp,current);
     	}

     	
     	current = current->next;
  	}
  	return (0);

}

int ft_add_modifier_to_prefab(t_env *e,xmlNode* current)
{
 	t_prefab *tmp;


	if (!(tmp = are_prefab(current,e->pref)))
		return (0);
	// printf("tmp name %s \n",tmp->prefab_name);
		ft_add_modi(current,tmp);
	return(0);
}