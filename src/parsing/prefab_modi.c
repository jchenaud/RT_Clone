/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prefab_modi.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchenaud <jchenaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/08 04:36:54 by jchenaud          #+#    #+#             */
/*   Updated: 2017/09/14 05:06:27 by jchenaud         ###   ########.fr       */
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

void ft_add_to_prefab(t_prefab *new_pref,t_env *e)
{
	t_prefab *tmp;
	tmp = e->pf_o;
	if (!e->pf_o)
	{
		e->pf_o = new_pref;
		e->pf_o->next = NULL;
		printf("adresse  on add %p \n", (e->pf_o->p_obj));

	}
	else
	{
		while (tmp->next != NULL)
			tmp = tmp->next;

		tmp->next = new_pref;
		tmp = tmp->next;
		tmp->next  = NULL;
	}
}



int cp_prefab(t_prefab *tmp_pref,t_env *e, xmlNode *current)
{
	t_prefab new_pref;

	ft_memcpy((&new_pref),tmp_pref,sizeof(t_prefab));

//	t_obj *tmp_aff;
//	tmp_aff = ((t_obj*)((t_list*)new_pref.p_obj)->content);

//	printf("x[%f] y [%f] z[%f]\n\n",tmp_aff->pos.x,tmp_aff->pos.y,tmp_aff->pos.z);
	ft_add_to_prefab(&new_pref,e);
  	ft_add_modi(current,&new_pref);
	//tmp_aff = ((t_obj*)((t_list*)e->pf_o->p_obj)->content);
//	printf("x[%f] y [%f] z[%f]\n\n",tmp_aff->pos.x,tmp_aff->pos.y,tmp_aff->pos.z);
//	printf("adresse  %p \n", (e->pf_o->p_obj));
//	printf("debug\n\n");
return(0);
}


void  	ft_include_to_pref(t_prefab *tmp,t_env *e, xmlNode *current)
{
 	  		cp_prefab(tmp,e,current);
}


  int ft_add_modifier_to_prefab(t_env *e,xmlNode* current)
  {
  	t_prefab *tmp;


  	if (!(tmp = are_prefab(current,e->pref)))
  		return (0);
  ft_include_to_pref(tmp,e,current);


	// printf("tmp name %s \n",tmp->prefab_name);
  	//ft_add_modi(current,tmp);
  	return(0);
  }