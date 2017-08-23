/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchenaud <jchenaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/21 16:08:40 by jchenaud          #+#    #+#             */
/*   Updated: 2017/08/23 13:27:51 by jchenaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libxml/parser.h>
#include <libxml/tree.h>
#include <string.h>
#include "objects.h"
#include "rt.h"
//#include "libft/include/libft.h"

// struct truc{
// 	char name[16];
// 	int n_params;
// 	char *params[5];
// }

// {"pos", 3, {"pos_x", "pos_y", "pos_z"}}

cl_float3 get_norm(xmlNode *current)
{
  cl_float3 norm;

  norm.x = ft_atof((char*)xmlGetProp( current, (const xmlChar*)"norm_x"));
  norm.y = ft_atof((char*)xmlGetProp( current, (const xmlChar*)"norm_y"));
  norm.z = ft_atof((char*)xmlGetProp( current, (const xmlChar*)"norm_z"));
  return (norm);
}

cl_float3 get_pos(xmlNode *current)
{
    cl_float3 pos;

  pos.x = ft_atof((char*)xmlGetProp( current, (const xmlChar*)"pos_x"));
  pos.y = ft_atof((char*)xmlGetProp( current, (const xmlChar*)"pos_y"));
  pos.z = ft_atof((char*)xmlGetProp( current, (const xmlChar*)"pos_z"));
  return (pos);
}

cl_float3 get_rot(xmlNode *current)
{
    cl_float3 rot;

  rot.x = ft_atof((char*)xmlGetProp( current, (const xmlChar*)"rot_x"));
  rot.y = ft_atof((char*)xmlGetProp( current, (const xmlChar*)"rot_y"));
  rot.z = ft_atof((char*)xmlGetProp( current, (const xmlChar*)"rot_z"));
  return (rot);
}


cl_uchar4 get_color(xmlNode *current)
{
  cl_uchar4 col;

  col.x = ft_atof((char*)xmlGetProp( current, (const xmlChar*)"R"));
  col.y = ft_atof((char*)xmlGetProp( current, (const xmlChar*)"B"));
  col.z = ft_atof((char*)xmlGetProp( current, (const xmlChar*)"V"));
  col.w = ft_atof((char*)xmlGetProp( current, (const xmlChar*)"T"));

  return (col);
}

// int get_pos_rot_obj(xmlNode* current, t_obj *new_obj)
// {
//   		if(!(current = current->children))
//   			return (-1);
//   		if (!(current = current->next))
//   			return (-1);

// 		if ( ft_strcmp((char*)current->name,"pos")== 0)
//    	 	{
//    	 		new_obj->pos.x = ft_atof((char*)xmlGetProp( current, (const xmlChar*)"pos_x"));
//    	 		new_obj->pos.y = ft_atof((char*)xmlGetProp( current, (const xmlChar*)"pos_y"));
//    	 		new_obj->pos.z = ft_atof((char*)xmlGetProp( current, (const xmlChar*)"pos_z"));

//      		 //printf( "  pos_x %f\n",new_obj->pos.x);
//      		 //printf( "  pos_y %f\n",new_obj->pos.y);
//      	 	 //printf( "  pos_z %f\n",new_obj->pos.z);
//     	}
//     	else 
//     		return (-1);

//     	if(!(current = current->next->next))
//   			return (- 1);
//   		////printf("name 2 =%s\n", current->name);
//     	if ( ft_strcmp((char*)current->name,"rot")== 0)
//    	 	{
//    	 		new_obj->rot.x = ft_atof((char*)xmlGetProp( current, (const xmlChar*)"rot_x"));
//    	 		new_obj->rot.y = ft_atof((char*)xmlGetProp( current, (const xmlChar*)"rot_y"));
//    	 		new_obj->rot.z = ft_atof((char*)xmlGetProp( current, (const xmlChar*)"rot_z"));

//      		 //printf( "  rot_x %f\n",new_obj->rot.x);
//      		 //printf( "  rot_y %f\n",new_obj->rot.y);
//      	 	 //printf( "  rot_z %f\n",new_obj->rot.z); 
     		
//     	}
//     	else
//     		return (-1);
//     	return(0);

// }



int pars_sphere( xmlNode* current, t_obj *new_obj)
{
		
		new_obj->type = SPHERE;
    if(!(current = current->children))
       return (-1);
     if (!(current = current->next))
       return (-1);

  		if (ft_strcmp((char*)current->name,"pos")== 0)
        new_obj->pos = get_pos(current);
      else
        return (-1);
      if(!(current = current->next->next))
        return (- 1);
      if (ft_strcmp((char*)current->name,"rot")== 0)
        new_obj->rot = get_rot(current);
      else
        return (-1);
      if(!(current = current->next->next))
        return (-1);
      if (ft_strcmp((char*)current->name,"col")== 0)
        new_obj->col = get_color(current);
      else
        return (-1);
      if(!(current = current->next->next))
        return (- 1);
    	if (ft_strcmp((char*)current->name,"rad")== 0)
    	{
    		new_obj->obj.sphere.rad = ft_atof((char*)xmlGetProp( current, (const xmlChar*)"rad"));
     	 	 //printf( "  rad %f\n",new_obj->obj.sphere.rad);
    	}
    	else
    		return (-1);
    	return (0);

}

int pars_pave( xmlNode* current, t_obj *new_obj)
{
		new_obj->type = PAVE;
    if(!(current = current->children))
       return (-1);
     if (!(current = current->next))
       return (-1);

      if (ft_strcmp((char*)current->name,"pos")== 0)
        new_obj->pos = get_pos(current);
      else
        return (-1);
      if(!(current = current->next->next))
        return (- 1);
      if (ft_strcmp((char*)current->name,"rot")== 0)
        new_obj->rot = get_rot(current);
      else
        return (-1);
      if(!(current = current->next->next))
        return (-1);
      if (ft_strcmp((char*)current->name,"col")== 0)
        new_obj->col = get_color(current);
      else
        return (-1);
      if(!(current = current->next->next))
        return (- 1);

    	if (ft_strcmp((char*)current->name,"size")== 0)
    	{
    		new_obj->obj.pave.size.x = ft_atof((char*)xmlGetProp( current, (const xmlChar*)"size_x"));
    		new_obj->obj.pave.size.y = ft_atof((char*)xmlGetProp( current, (const xmlChar*)"size_y"));
    		new_obj->obj.pave.size.z = ft_atof((char*)xmlGetProp( current, (const xmlChar*)"size_z"));

     	 	 //printf( "  rad %f\n",new_obj->obj.pave.size.x);
     	 	 //printf( "  rad %f\n",new_obj->obj.pave.size.y);
     	 	 //printf( "  rad %f\n",new_obj->obj.pave.size.z);
    	}
    	else
    		return (-1);

    	return(0);

}

int pars_plan( xmlNode* current, t_obj *new_obj)
{ 

		new_obj->type = PLAN;
  		if(!(current = current->children))
       return (-1);
     if (!(current = current->next))
       return (-1);

      if (ft_strcmp((char*)current->name,"pos")== 0)
        new_obj->pos = get_pos(current);
      else
        return (-1);
      if(!(current = current->next->next))
        return (- 1);
      if (ft_strcmp((char*)current->name,"rot")== 0)
        new_obj->rot = get_rot(current);
      else
        return (-1);
      if(!(current = current->next->next))
        return (-1);
      if (ft_strcmp((char*)current->name,"col")== 0)
        new_obj->col = get_color(current);
      else
        return (-1);
      if(!(current = current->next->next))
        return (- 1);

    	if (ft_strcmp((char*)current->name,"norm")== 0)
        new_obj->obj.plan.norm = get_norm(current);
    	else
    		return (-1);

    	return(0);

}

int pars_cone( xmlNode* current, t_obj *new_obj)
{ 

		new_obj->type = CONE;

  		if(!(current = current->children))
       return (-1);
     if (!(current = current->next))
       return (-1);

      if (ft_strcmp((char*)current->name,"pos")== 0)
        new_obj->pos = get_pos(current);
      else
        return (-1);
      if(!(current = current->next->next))
        return (- 1);
      if (ft_strcmp((char*)current->name,"rot")== 0)
        new_obj->rot = get_rot(current);
      else
        return (-1);
      if(!(current = current->next->next))
        return (-1);
      if (ft_strcmp((char*)current->name,"col")== 0)
        new_obj->col = get_color(current);
      else
        return (-1);
      if(!(current = current->next->next))
        return (- 1);

    	if (ft_strcmp((char*)current->name,"norm")== 0)
    		new_obj->obj.cone.norm = get_norm(current);
    	else
    		return (-1);

  		if(!(current = current->next->next))
  			return (- 1);

    	if (ft_strcmp((char*)current->name,"angle")== 0)
    		new_obj->obj.cone.angle = ft_atof((char*)xmlGetProp( current, (const xmlChar*)"angle"));
    	else
    		return (-1);

    	return(0);

}


int pars_cylinder( xmlNode* current, t_obj *new_obj)
{ 

		new_obj->type = CYLINDER;
  		if(!(current = current->children))
       return (-1);
     if (!(current = current->next))
       return (-1);

      if (ft_strcmp((char*)current->name,"pos")== 0)
        new_obj->pos = get_pos(current);
      else
        return (-1);
      if(!(current = current->next->next))
        return (- 1);
      if (ft_strcmp((char*)current->name,"rot")== 0)
        new_obj->rot = get_rot(current);
      else
        return (-1);
      if(!(current = current->next->next))
        return (-1);
      if (ft_strcmp((char*)current->name,"col")== 0)
        new_obj->col = get_color(current);
      else
        return (-1);
      if(!(current = current->next->next))
        return (- 1);

    	if (ft_strcmp((char*)current->name,"norm")== 0)
        new_obj->obj.cylinder.norm = get_norm(current);
    	else
    		return (-1);

  		if(!(current = current->next->next))
  			return (- 1);

    	if (ft_strcmp((char*)current->name,"rad")== 0)
    		new_obj->obj.cylinder.rad = ft_atof((char*)xmlGetProp( current, (const xmlChar*)"rad"));
     	 	 
    	else
    		return (-1);

    	return(0);

}


int pars_cam( xmlNode* current, t_cam *new_cam)
{ 
  		if(!(current = current->children))
  			return (-1);
  		if (!(current = current->next))
  			return (-1);
   		if ( ft_strcmp((char*)current->name,"pos")== 0)
   	 	{
   	 		new_cam->pos.x = ft_atof((char*)xmlGetProp( current, (const xmlChar*)"pos_x"));
   	 		new_cam->pos.y = ft_atof((char*)xmlGetProp( current, (const xmlChar*)"pos_y"));
   	 		new_cam->pos.z = ft_atof((char*)xmlGetProp( current, (const xmlChar*)"pos_z"));

     		 //printf( "  pos_x %f\n",new_cam->pos.x);
     		 //printf( "  pos_y %f\n",new_cam->pos.y);
     	 	 //printf( "   pos_z %f\n",new_cam->pos.z);
    	}
    	else
    		return (-1);

    	if(!(current = current->next->next))
  			return (- 1);

    	if (ft_strcmp((char*)current->name,"dir")== 0)
    	{
    		new_cam->dir.x = ft_atof((char*)xmlGetProp( current, (const xmlChar*)"dir_x"));
    		new_cam->dir.y = ft_atof((char*)xmlGetProp( current, (const xmlChar*)"dir_y"));
    		new_cam->dir.z = ft_atof((char*)xmlGetProp( current, (const xmlChar*)"dir_z"));

     	 	 //printf( "  dir %f\n",new_cam->dir.x);
     	 	 //printf( "  dir %f\n",new_cam->dir.y);
     	 	 //printf( "  dir %f\n",new_cam->dir.z);


    	}
    	else
    		return (-1);

  		if(!(current = current->next->next))
  			return (- 1);
    	if ( ft_strcmp((char*)current->name,"rot")== 0)
   	 	{
   	 		new_cam->rot.x = ft_atof((char*)xmlGetProp( current, (const xmlChar*)"rot_x"));
   	 		new_cam->rot.y = ft_atof((char*)xmlGetProp( current, (const xmlChar*)"rot_y"));
   	 		new_cam->rot.z = ft_atof((char*)xmlGetProp( current, (const xmlChar*)"rot_z"));
     		 //printf( "  rot_x %f\n",new_cam->rot.x);
     		 //printf( "  rot_y %f\n",new_cam->rot.y);
     	 	 //printf( "  rot_z %f\n",new_cam->rot.z);
     		
    	}
    	else
    		return (-1);

  		if(!(current = current->next->next))
  			return (- 1);

    	if ( ft_strcmp((char*)current->name,"fov")== 0)
   	 	{
   	 		new_cam->fov.x = ft_atof((char*)xmlGetProp( current, (const xmlChar*)"fov_x"));
   	 		new_cam->fov.y = ft_atof((char*)xmlGetProp( current, (const xmlChar*)"fov_y"));
   	 		//printf( "  fov_x %f\n",new_cam->fov.x);
     		 //printf( " fov_y %f\n",new_cam->fov.y);
   	 	}
   	 	else
    		return (-1);

  		if(!(current = current->next->next))
  			return (- 1);

    	if (ft_strcmp((char*)current->name,"dis")== 0)
    	{
    		new_cam->dis = ft_atof((char*)xmlGetProp( current, (const xmlChar*)"dis"));
     	 	 //printf( " dis %f\n",new_cam->dis);

    	}
    	else
    		return (-1);

    	if(!(current = current->next->next))
  			return (- 1);
    
    	if (ft_strcmp((char*)current->name,"w")== 0)
    	{
    		new_cam->w = ft_atof((char*)xmlGetProp( current, (const xmlChar*)"w"));
     	 	 //printf( " w %u\n",new_cam->w);

    	}
    	else
    		return (-1);
    	if(!(current = current->next->next))
  			return (- 1);
    
    	if (ft_strcmp((char*)current->name,"h")== 0)
    	{
    		new_cam->h = ft_atof((char*)xmlGetProp( current, (const xmlChar*)"h"));
     	 	 //printf( " h %u\n",new_cam->h);

    	}
    	else
    		return (-1);

    	return(0);

}

int pars_light( xmlNode* current, t_light *new_light)
{ 
  		if(!(current = current->children))
  			return (-1);
  		if (!(current = current->next))
  			return (-1);
		
		if ( ft_strcmp((char*)current->name,"pos")== 0)
   	 	{
   	 		new_light->pos.x = ft_atof((char*)xmlGetProp( current, (const xmlChar*)"pos_x"));
   	 		new_light->pos.y = ft_atof((char*)xmlGetProp( current, (const xmlChar*)"pos_y"));
   	 		new_light->pos.z = ft_atof((char*)xmlGetProp( current, (const xmlChar*)"pos_z"));
   	 	}
   	 	else
   	 		return (-1);

   	 	if(!(current = current->next->next))
  			return (- 1);
  		if ( ft_strcmp((char*)current->name,"col")== 0)
   	 	{
   	 		new_light->col.x = ft_atof((char*)xmlGetProp( current, (const xmlChar*)"R"));
   	 		new_light->col.y = ft_atof((char*)xmlGetProp( current, (const xmlChar*)"V"));
   	 		new_light->col.z = ft_atof((char*)xmlGetProp( current, (const xmlChar*)"B"));
   	 		new_light->col.w = ft_atof((char*)xmlGetProp( current, (const xmlChar*)"T"));

   	 	}
   	 	else
   	 		return (-1);

   	 	if(!(current = current->next->next))
  			return (- 1);

   		if ( ft_strcmp((char*)current->name,"i")== 0)
   	 	{
   	 		new_light->i.x = ft_atof((char*)xmlGetProp( current, (const xmlChar*)"amb"));
   	 		new_light->i.y = ft_atof((char*)xmlGetProp( current, (const xmlChar*)"dif"));
   	 		new_light->i.z = ft_atof((char*)xmlGetProp( current, (const xmlChar*)"spec"));
   	 	}
   	 	else
   	 		return(-1);
   	 	return (0);
}





int pars_content( xmlNode* root, t_env *e)
{
t_obj  new_obj;
t_cam  new_cam;
t_light new_light;

// ft_lstadd(&e->obj, ft_lstnew(&new_obj, sizeof(t_obj)));
// ft_lstadd(&e->cam, ft_lstnew(&new_obj, sizeof(t_cam)));
// ft_lstadd(&e->light, ft_lstnew(&new_obj, sizeof(t_light)));




  xmlNode* current = NULL;
  for ( current=root; current!=NULL; current=current->next )
  {
    if ( current->type==XML_ELEMENT_NODE )
      //printf( "node type: %s\n", current->name );
  	if (ft_strcmp((char*)current->name,"sphere")== 0)
	{
		if(pars_sphere(current, &new_obj) == -1)
			return (-1);
		ft_lstadd(&e->obj, ft_lstnew(&new_obj, sizeof(t_obj)));
		//printf("rad sph  = %f \n", new_obj.obj.sphere.rad);
	}
	if (ft_strcmp((char*)current->name,"pave")== 0)
	{
		if(pars_pave(current, &new_obj) == -1)
			return (-1);
		ft_lstadd(&e->obj, ft_lstnew(&new_obj, sizeof(t_obj)));

	}
	if (ft_strcmp((char*)current->name,"plan")== 0)
	{
		if(pars_plan(current, &new_obj) == -1)
			return (-1);
		ft_lstadd(&e->obj, ft_lstnew(&new_obj, sizeof(t_obj)));

	}

	if (ft_strcmp((char*)current->name,"cone")== 0)
	{
		if(pars_cone(current, &new_obj) == -1)
			return (-1);
		ft_lstadd(&e->obj, ft_lstnew(&new_obj, sizeof(t_obj)));

	}
	if (ft_strcmp((char*)current->name,"cylinder")== 0)
	{
		if(pars_cylinder(current, &new_obj) == -1)
			return (-1);
		ft_lstadd(&e->obj, ft_lstnew(&new_obj, sizeof(t_obj)));

	}
	if (ft_strcmp((char*)current->name,"cam")== 0)
	{
		if(pars_cam(current, &new_cam) == -1)
			return (-1);
		ft_lstadd(&e->cam, ft_lstnew(&new_obj, sizeof(t_cam)));

	}
	if (ft_strcmp((char*)current->name,"light") == 0)
	{
		if(pars_light(current, &new_light) == -1)
			return (-1);
		ft_lstadd(&e->light, ft_lstnew(&new_obj, sizeof(t_light)));
	}

    else if (!ft_strcmp((char*)current->name,"scene"))
    {
    	pars_content(current->children,e);
    	//return (-1);
    }
    // if(current->next != NULL)
    // current=current->next;
    // //printf("for have make \n");
    //print_content( current->children );
  }
  return (0);
}
 
int parsing(char *file, t_env *e)
{

  xmlDoc*  doc  = NULL;
  xmlNode* root = NULL;
  doc = xmlReadFile( file, NULL, 0 );
   
  if ( doc==NULL )
    return -1;
   
  root = xmlDocGetRootElement( doc );
  if (pars_content( root, e )== -1)
    return (-1);
  xmlFreeDoc( doc );
  xmlCleanupParser();
   
  return 0;
}