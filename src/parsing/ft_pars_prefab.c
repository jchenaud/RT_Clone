/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pars_prefab.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchenaud <jchenaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/06 01:53:33 by jchenaud          #+#    #+#             */
/*   Updated: 2017/09/10 04:32:51 by jchenaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libxml/xmlmemory.h"
#include "rt.h"


int ft_pars_prefab(t_env *e, xmlNode* current)
{


 	 t_obj  new_obj;
 	 e->pref->p_obj = NULL;

 	 t_list *tmp_af;

 	 tmp_af = e->pref->p_obj;

	if (ft_strcmp((char*)current->name, "prefab") != 0)
      return (-1);
  if(!(current = current->children))
  	return(-1);
  if(!(current = current->next))
  	return(-1);

 	while (current != NULL)
  	{ 
		if ( current->type==XML_ELEMENT_NODE ) // sert a quoi
    	{
    	  if (ft_strcmp((char*)current->name,"sphere")== 0)
   		   {
       			if(pars_sphere(current, &new_obj) == -1)
          			return (-1);
 	  			ft_lstadd(&e->pref->p_obj, ft_lstnew(&new_obj, sizeof(t_obj)));
     		}
     		else if (ft_strcmp((char*)current->name,"pave")== 0)
			{
				if(pars_pave(current, &new_obj) == -1)
					return (-1);
			ft_lstadd(&e->pref->p_obj, ft_lstnew(&new_obj, sizeof(t_obj)));

			}
			else if (ft_strcmp((char*)current->name,"plan")== 0)
			{
				if(pars_plan(current, &new_obj) == -1)
					return (-1);
				ft_lstadd(&e->pref->p_obj, ft_lstnew(&new_obj, sizeof(t_obj)));

			}
			else if (ft_strcmp((char*)current->name,"cone")== 0)
			{
				if(pars_cone(current, &new_obj) == -1)
					return (-1);
				ft_lstadd(&e->pref->p_obj, ft_lstnew(&new_obj, sizeof(t_obj)));

			}
			else if (ft_strcmp((char*)current->name,"cylinder")== 0)
			{
				if(pars_cylinder(current, &new_obj) == -1)
					return (-1);
				ft_lstadd(&e->pref->p_obj, ft_lstnew(&new_obj, sizeof(t_obj)));
			}

		}
    current = current->next;

	 }
	 return (0);
}























































































// {
// 	xmlNode* current = NULL;
// 	t_prefab *pref_lst;
// 	t_obj  new_obj;

// 	current = xmlDocGetRootElement( doc );
// 	if (ft_strcmp((char*)current->name, "prefab") != 0)
//       return (-1);

//   if(!(current = current->children))
//   	return(-1);
//   if(!(current = current->next))
//   	return(-1); 
//   ft_lstadd(&e->pref,e->pref);
//   ft_lstadd(&pref_lst,pref_lst);

// 	//pref_lst =  ft_lstnew(&(t_list*)pref_lst,sizeof(t_prefab));
// 	while (current != NULL)
// 	{ 
// 		if ( current->type==XML_ELEMENT_NODE ) // sert a quoi
// 		{
// 			if (ft_strcmp((char*)current->name,"sphere")== 0)
// 			{
// 				// // printf("sphere find \n");
// 				if(pars_sphere(current, &new_obj) == -1)
// 				 	return (-1);
// 				 // printf("a que coucou patrik %p\n", e->pref);
// 				 ft_lstadd(&pref_lst->p_obj, ft_lstnew(&new_obj, sizeof(t_obj)));
// 				 // printf("a que coucou bob %f \n",pref_lst->p_obj->pos.x);

	//		}
			// else if (ft_strcmp((char*)current->name,"pave")== 0)
			// {
			// 	if(pars_pave(current, &new_obj) == -1)
			// 		return (-1);
			// 	ft_lstadd(&((t_prefab*)e->pref->content)->p_obj, ft_lstnew(&new_obj, sizeof(t_obj)));
			// }
			// else if (ft_strcmp((char*)current->name,"plan")== 0)
			// {
			// 	if(pars_plan(current, &new_obj) == -1)
			// 		return (-1);
			// 	ft_lstadd(&((t_prefab*)e->pref->content)->p_obj, ft_lstnew(&new_obj, sizeof(t_obj)));
			// }
			// else if (ft_strcmp((char*)current->name,"cone")== 0)
			// {
			// 	if(pars_cone(current, &new_obj) == -1)
			// 		return (-1);
			// 	ft_lstadd(&((t_prefab*)e->pref->content)->p_obj, ft_lstnew(&new_obj, sizeof(t_obj)));
			// }
			// else if (ft_strcmp((char*)current->name,"cylinder")== 0)
			// {
			// 	if(pars_cylinder(current, &new_obj) == -1)
			// 		return (-1);
	// 		// 	ft_lstadd(&((t_prefab*)e->pref->content)->p_obj, ft_lstnew(&new_obj, sizeof(t_obj)));
	// 		// }

	// 	}
	// 	 current = current->next;
	// }
// }
