/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/21 16:08:40 by jchenaud          #+#    #+#             */
/*   Updated: 2017/08/29 05:30:46 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "rt.h"
//#include "libft/include/libft.h"

// struct truc{
// 	char name[16];
// 	int n_params;
// 	char *params[5];
// }

// {"pos", 3, {"pos_x", "pos_y", "pos_z"}}


int ztab(int* tab, int size)
{
	int i;
	i = 0;
	while (i < size)
	{
		if (tab[i] == 0)
			return(0);
		i++;
	}
	//printf("espris espris et tu la\n");
	return (1);

}

cl_float3 get_pos(xmlNode *current)
{
	cl_float3 pos;

	if ((!(xmlGetProp(current,(const xmlChar*)"pos_x"))) || 
			((!(xmlGetProp(current,(const xmlChar*)"pos_y")))) ||
			(!(xmlGetProp(current,(const xmlChar*)"pos_z"))))
		exit (0);

	pos.x = ft_atof((char*)xmlGetProp( current, (const xmlChar*)"pos_x"));
	pos.y = ft_atof((char*)xmlGetProp( current, (const xmlChar*)"pos_y"));
	pos.z = ft_atof((char*)xmlGetProp( current, (const xmlChar*)"pos_z"));
	return (pos);
}

cl_float3 get_rot(xmlNode *current)
{
	cl_float3 rot;

	if ((!(xmlGetProp(current,(const xmlChar*)"rot_x"))) || 
			((!(xmlGetProp(current,(const xmlChar*)"rot_y")))) ||
			(!(xmlGetProp(current,(const xmlChar*)"rot_z"))))
		exit (0);

	rot.x = ft_atof((char*)xmlGetProp( current, (const xmlChar*)"rot_x"));
	rot.y = ft_atof((char*)xmlGetProp( current, (const xmlChar*)"rot_y"));
	rot.z = ft_atof((char*)xmlGetProp( current, (const xmlChar*)"rot_z"));
	return (rot);
}



t_color   get_color(xmlNode *current)
{
	t_color col;

	if ((!(xmlGetProp(current,(const xmlChar*)"R"))) || 
			((!(xmlGetProp(current,(const xmlChar*)"B")))) ||
			(!(xmlGetProp(current,(const xmlChar*)"V"))) ||
			(!(xmlGetProp(current,(const xmlChar*)"T"))))
		exit(0);

	col.r = ft_atou((char*)xmlGetProp( current, (const xmlChar*)"R"));
	col.g = ft_atou((char*)xmlGetProp( current, (const xmlChar*)"V"));
  col.b = ft_atou((char*)xmlGetProp( current, (const xmlChar*)"B"));
	col.a = ft_atou((char*)xmlGetProp( current, (const xmlChar*)"T"));

	return (col);
}

cl_float3 get_norm(xmlNode *current)
{
	cl_float3 norm;

	if ((!(xmlGetProp(current,(const xmlChar*)"norm_x"))) || 
			((!(xmlGetProp(current,(const xmlChar*)"norm_y")))) ||
			(!(xmlGetProp(current,(const xmlChar*)"norm_z"))))
		exit (0);

	norm.x = ft_atof((char*)xmlGetProp( current, (const xmlChar*)"norm_x"));
	norm.y = ft_atof((char*)xmlGetProp( current, (const xmlChar*)"norm_y"));
	norm.z = ft_atof((char*)xmlGetProp( current, (const xmlChar*)"norm_z"));
	return (norm);
}

cl_float3 get_size(xmlNode *current)
{
	cl_float3 size;

	if ((!(xmlGetProp(current,(const xmlChar*)"size_x"))) || 
			((!(xmlGetProp(current,(const xmlChar*)"size_y")))) ||
			(!(xmlGetProp(current,(const xmlChar*)"size_z"))))
		exit (0);

	size.x = ft_atof((char*)xmlGetProp( current, (const xmlChar*)"size_x"));
	size.y = ft_atof((char*)xmlGetProp( current, (const xmlChar*)"size_y"));
	size.z = ft_atof((char*)xmlGetProp( current, (const xmlChar*)"size_z"));
	return (size);
}

cl_float3 get_dir(xmlNode *current)
{
	cl_float3 dir;

	if ((!(xmlGetProp(current,(const xmlChar*)"dir_x"))) || 
			((!(xmlGetProp(current,(const xmlChar*)"dir_y")))) ||
			(!(xmlGetProp(current,(const xmlChar*)"dir_z"))))
		exit (0);

	dir.x = ft_atof((char*)xmlGetProp( current, (const xmlChar*)"dir_x"));
	dir.y = ft_atof((char*)xmlGetProp( current, (const xmlChar*)"dir_y"));
	dir.z = ft_atof((char*)xmlGetProp( current, (const xmlChar*)"dir_z"));
	return (dir);
}

cl_float2 get_fov(xmlNode *current)
{
	cl_float2 fov;

	if ((!(xmlGetProp(current,(const xmlChar*)"fov_x"))) || 
			(!(xmlGetProp(current,(const xmlChar*)"fov_y"))))
		exit (0);

	fov.x = ft_atof((char*)xmlGetProp( current, (const xmlChar*)"fov_x"));
	fov.y = ft_atof((char*)xmlGetProp( current, (const xmlChar*)"fov_y"));
	return (fov);
}


cl_float3 get_light_fac(xmlNode *current)
{
	cl_float3 i;

	if ((!(xmlGetProp(current,(const xmlChar*)"amb"))) || 
			((!(xmlGetProp(current,(const xmlChar*)"dif")))) ||
			(!(xmlGetProp(current,(const xmlChar*)"spec"))))
		exit (0);

	i.x = ft_atof((char*)xmlGetProp( current, (const xmlChar*)"amb"));
	i.y = ft_atof((char*)xmlGetProp( current, (const xmlChar*)"dif"));
	i.z = ft_atof((char*)xmlGetProp( current, (const xmlChar*)"spec"));

	return (i);
}

cl_float get_rad (xmlNode *current)
{

	cl_float rad;
	if (!(xmlGetProp(current,(const xmlChar*)"rad")))
		exit (0);

	rad = ft_atof((char*)xmlGetProp( current, (const xmlChar*)"rad"));
	return (rad);
}

cl_float get_ang(xmlNode *current)
{

	cl_float angle;

	if (!(xmlGetProp(current,(const xmlChar*)"angle")))
		exit (0);
	angle = ft_atof((char*)xmlGetProp( current, (const xmlChar*)"angle"));
	return(angle);
}


cl_float get_dis(xmlNode *current)
{

	cl_float dis;

	if (!(xmlGetProp(current,(const xmlChar*)"dis")))
		exit (0);
	dis = ft_atof((char*)xmlGetProp( current, (const xmlChar*)"dis"));
	return(dis);
}

cl_uint get_w(xmlNode *current)
{

	cl_uint w;

	if (!(xmlGetProp(current,(const xmlChar*)"w")))
		exit (0);
	w = ft_atoi((char*)xmlGetProp( current, (const xmlChar*)"w"));
	return(w);
}

cl_uint get_h(xmlNode *current)
{

	cl_uint h;

	if (!(xmlGetProp(current,(const xmlChar*)"h")))
		exit (0);
	h = ft_atoi((char*)xmlGetProp( current, (const xmlChar*)"h"));
	return(h);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void    pars_sphere_anex(int * tab, xmlNode *current, t_obj *new_obj)
{
  if (ft_strcmp((char*)current->name,"pos")== 0)
  {
    new_obj->pos = get_pos(current);
    tab[0] = 1;
  }
  else if (ft_strcmp((char*)current->name,"rot")== 0)
  {
    new_obj->rot = get_rot(current);
    tab[1] = 1;
  }
  else if (ft_strcmp((char*)current->name,"col")== 0)
  {
    new_obj->col = get_color(current);
    tab[2] = 1;
  }
  else if (ft_strcmp((char*)current->name,"rad")== 0)
  {
    new_obj->obj.sphere.rad = get_rad(current);
    tab[3] = 1;
  }
  else
    exit (0);
}


int pars_sphere( xmlNode* current, t_obj *new_obj)
{
int tab[4] = {0};
int i;

  i = 0;
  new_obj->type = SPHERE;
  //ft_bzero((void*)tab,3);
  if(!(current = current->children))
    return (-1);
  while (ztab(tab,4)==0)
  {
  // printf("%d\n",i);
    if (i == 0)
    {
      if (!(current = current->next))
        return (-1);
    }
    else
      if(!(current = current->next->next))
        return (- 1);
    pars_sphere_anex(tab,current,new_obj);
  i++;
}
	return (0);

}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void   pars_pave_anex(int * tab, xmlNode *current, t_obj *new_obj)
{
  if (ft_strcmp((char*)current->name,"pos")== 0)
  {
    new_obj->pos = get_pos(current);
    tab[0] = 1;
  }
  else if (ft_strcmp((char*)current->name,"rot")== 0)
  {
    new_obj->rot = get_rot(current);
    tab[1] = 1;
  }
  else if (ft_strcmp((char*)current->name,"col")== 0)
  {
    new_obj->col = get_color(current);
    tab[2] = 1;
  }
  else if (ft_strcmp((char*)current->name,"size")== 0)
  {
    new_obj->obj.pave.size = get_size(current);
    tab[3] = 1;
  }
  else
    exit (0);
  //return(tab);

}

int pars_pave( xmlNode* current, t_obj *new_obj)
{
int tab[4] = {0};
int i;

  i = 0;
  new_obj->type = PAVE;
  //ft_bzero((void*)tab,3);
  if(!(current = current->children))
    return (-1);
  while (ztab(tab,4)==0)
  {
  //  printf("%d\n",i);
    if (i == 0)
    {
      if (!(current = current->next))
        return (-1);
    }
    else
      if(!(current = current->next->next))
        return (- 1);
  pars_pave_anex(tab,current,new_obj);
  //printf("%d %d %d %d\n",tab[0],tab[1],tab[2],tab[3]);
  i++;
}
	return(0);
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void   pars_plan_anex(int *tab, xmlNode *current, t_obj *new_obj)
{
  if (ft_strcmp((char*)current->name,"pos")== 0)
  {
    new_obj->pos = get_pos(current);
    tab[0] = 1;
  }
  else if (ft_strcmp((char*)current->name,"rot")== 0)
  {
    new_obj->rot = get_rot(current);
    tab[1] = 1;
  }
  else if (ft_strcmp((char*)current->name,"col")== 0)
  {
    new_obj->col = get_color(current);
    tab[2] = 1;
  }
  else if (ft_strcmp((char*)current->name,"norm")== 0)
  {
    new_obj->obj.plan.norm = get_norm(current);
    tab[3] = 1;
  }
  else
    exit (0);
}

int pars_plan( xmlNode* current, t_obj *new_obj)
{ 

int tab[4] = {0};
int i;

  i = 0;
  new_obj->type = PLAN;
  //ft_bzero((void*)tab,3);
  if(!(current = current->children))
    return (-1);
  while (ztab(tab,4)==0)
  {
  //  printf("%d\n",i);
    if (i == 0)
    {
      if (!(current = current->next))
        return (-1);
    }
    else
      if(!(current = current->next->next))
        return (- 1);
      pars_plan_anex(tab, current, new_obj);

  i++;
}
	return(0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void   pars_cone_anex2(int *tab, xmlNode *current, t_obj *new_obj,int find)
{
  if (find == 1)
    return ;
  else if (ft_strcmp((char*)current->name,"norm")== 0)
  {
    new_obj->obj.cone.norm = get_norm(current);
    tab[3] = 1;
  }
  else if (ft_strcmp((char*)current->name,"angle")== 0)
  {
    new_obj->obj.cone.angle =  get_ang(current);
    tab[4] = 1;
  }
  else 
      exit(0);

}

void   pars_cone_anex(int *tab, xmlNode *current, t_obj *new_obj)
{
  int find;

  find = 0;
  if (ft_strcmp((char*)current->name,"pos")== 0)
  {
    new_obj->pos = get_pos(current);
    tab[0] = 1;
    find = 1;
  }
  else if (ft_strcmp((char*)current->name,"rot")== 0)
  {
    new_obj->rot = get_rot(current);
    tab[1] = 1;
    find = 1;
  }
  else if (ft_strcmp((char*)current->name,"col")== 0)
  {
    new_obj->col = get_color(current);
    tab[2] = 1;
    find = 1;
  }
  pars_cone_anex2(tab, current, new_obj, find); 
}

int pars_cone( xmlNode* current, t_obj *new_obj)
{ 
  int tab[5] = {0};
  int i;

  i = 0;
  new_obj->type = CONE;
  //ft_bzero((void*)tab,3);
  if(!(current = current->children))
    return (-1);
  while (ztab(tab,5)==0)
  {
  //  printf("%d\n",i);
    if (i == 0)
    {
      if (!(current = current->next))
        return (-1);
    }
    else
      if(!(current = current->next->next))
        return (- 1);
    pars_cone_anex(tab,current,new_obj);
  i++;
}
	return(0);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



void   pars_cylinder_anex2(int *tab, xmlNode *current, t_obj *new_obj, int find)
{
  if (find == 1)
    return ;
  else if (ft_strcmp((char*)current->name,"norm")== 0)
  {
    new_obj->obj.cylinder.norm = get_norm(current);
    tab[3] = 1;
  }

  else if (ft_strcmp((char*)current->name,"rad")== 0)
  {
    new_obj->obj.sphere.rad = get_rad(current); 
    tab[4] = 1;
  }
  else
    exit (0);

}

void   pars_cylinder_anex(int *tab, xmlNode *current, t_obj *new_obj)
{
  int find;

  find = 0;
  if (ft_strcmp((char*)current->name,"pos")== 0)
  {
    new_obj->pos = get_pos(current);
    tab[0] = 1;
    find = 1;
  }

  else if (ft_strcmp((char*)current->name,"rot")== 0)
  {
    new_obj->rot = get_rot(current);
    tab[1] = 1;
    find = 1;
  }

  else if (ft_strcmp((char*)current->name,"col")== 0)
  {
    new_obj->col = get_color(current);
    tab[2] = 1;
    find = 1;
  }
  pars_cylinder_anex2(tab, current, new_obj, find);



}


int pars_cylinder( xmlNode* current, t_obj *new_obj)
{ 

	 int tab[5] = {0};
  int i;

  i = 0;
  new_obj->type = CYLINDER;
  //ft_bzero((void*)tab,3);
  if(!(current = current->children))
    return (-1);
  while (ztab(tab,5)==0)
  {
  //  printf("%d\n",i);
    if (i == 0)
    {
      if (!(current = current->next))
        return (-1);
    }
    else
      if(!(current = current->next->next))
        return (- 1);
  pars_cylinder_anex(tab, current, new_obj);
  i++;
}
	return(0);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void   pars_cam_anex3(int *tab, xmlNode *current, t_cam *new_cam, int find)
{
  if (find == 1)
    return ;
  else if (ft_strcmp((char*)current->name,"w")== 0)
    {
      new_cam->w =  get_w(current);
      tab[5] = 1;
    }
    else if (ft_strcmp((char*)current->name,"h")== 0)
    {
      new_cam->h =  get_h(current);
      tab[6] = 1;
    }
    else
      exit(0);
  }

void   pars_cam_anex2(int *tab, xmlNode *current, t_cam *new_cam, int find)
{
  if (find == 1)
    return;
  else if ( ft_strcmp((char*)current->name,"fov")== 0)
    {
      new_cam->fov = get_fov(current);
      tab[3] = 1;
      find = 1;
    }
  else if (ft_strcmp((char*)current->name,"dis")== 0)
    {
      new_cam->dis = get_dis(current);
      tab[4] = 1;
      find = 1;
    }
    pars_cam_anex3(tab,current,new_cam,find);
}


void   pars_cam_anex(int *tab, xmlNode *current, t_cam *new_cam)
{
  int find;

  find = 0;

    if (ft_strcmp((char*)current->name,"pos")== 0)
    {
      new_cam->pos = get_pos(current); //printf( "   pos_z %f\n",new_cam->pos.z);
      tab[0] = 1;
    find = 1;
    }
    else if (ft_strcmp((char*)current->name,"dir")== 0)
    {
      new_cam->dir =  get_dir(current);
      tab[1] = 1;
    find = 1;
    }
    else if (ft_strcmp((char*)current->name,"rot")== 0)
    {
      new_cam->rot = get_rot(current);
      tab[2] = 1;
    find = 1;
    }
    pars_cam_anex2(tab,current,new_cam,find);
}

int pars_cam( xmlNode* current, t_cam *new_cam)
{ 
	int tab[7] = {0};
	int i;

	i = 0;
	//ft_bzero((void*)tab,3);
	if(!(current = current->children))
		return (-1);
	while (ztab(tab,7)==0)
	{
	//	printf("%d\n",i);
		if (i == 0)
		{
			if (!(current = current->next))
				return (-1);
		}
		else
			if(!(current = current->next->next))
				return (- 1);
	 pars_cam_anex(tab,current,new_cam);
		i++;
	}
	return(0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



void   pars_light_anex(int *tab, xmlNode *current, t_light *new_light)
{
    if(ft_strcmp((char*)current->name,"pos")== 0)
    {
      new_light->pos = get_pos(current);
      tab[0] = 1;
    }
    else if(ft_strcmp((char*)current->name,"col")== 0)
    {
      new_light->col = get_color(current);
      tab[1] = 1;
    }
    else if ( ft_strcmp((char*)current->name,"i")== 0)
    {
      new_light->i = get_light_fac(current);
      tab[2] = 1;
    }
    else
      exit (0);    
}

int pars_light( xmlNode* current, t_light *new_light)
{ 
	int tab[3] = {0};
	int i;

	i = 0;
	//ft_bzero((void*)tab,3);
	if(!(current = current->children))
		return (-1);
	while (ztab(tab,3))
	{
		if (i == 0)
		{
			if (!(current = current->next))
				return (-1);
		}
		else
			if(!(current = current->next->next))
				return (- 1);
      pars_light_anex(tab, current, new_light);
		i++;
	}
	return (0);
}






int pars_content( xmlNode* root, t_env *e)
{
	t_obj  new_obj;
	t_cam  new_cam;
	t_light new_light;

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
			ft_lstadd(&e->cam, ft_lstnew(&new_cam, sizeof(t_cam)));

		}
		if (ft_strcmp((char*)current->name,"light") == 0)
		{
			if(pars_light(current, &new_light) == -1)
				return (-1);
			ft_lstadd(&e->light, ft_lstnew(&new_light, sizeof(t_light)));
		}


		// reste les heatbox a faire 

		else if (!ft_strcmp((char*)current->name,"scene"))
		{
			pars_content(current->children,e);
			//return (-1);
		}

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
