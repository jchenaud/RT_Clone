/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchenaud <jchenaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/21 16:08:40 by jchenaud          #+#    #+#             */
/*   Updated: 2017/09/10 04:32:09 by jchenaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libxml/xmlmemory.h"
#include "rt.h"
//#include "libft/include/libft.h"

// struct truc{
//  char name[16];
//  int n_params;
//  char *params[5];
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
  ////// printf("espris espris et tu la\n");
  return (1);

}
// ///////////////////////////________ a voire pour optis  le function get()_______________________
cl_float get_float_xml(char *name, xmlNode * current)
{
   char  *data;
   cl_float n;

   data = (char*)xmlGetProp(current,(const xmlChar*)name);
      if (!data)
       return (0.00);
    n = ft_atof(data);
    free(data);
    return (n);
}

cl_uchar get_uchar_xml(char *name, xmlNode * current)
{
   char  *data;
   cl_uchar c;

   data = (char*)xmlGetProp(current,(const xmlChar*)name);
      if (!data)
       return (0);
    c = ft_atou(data);
    free(data);
    return (c);
}

cl_uint get_uint_xml(char *name, xmlNode * current)
{
   char  *data;
   cl_uint i;

   data = (char*)xmlGetProp(current,(const xmlChar*)name);
      if (!data)
       return (0);
    i = ft_atoi(data);
    free(data);
    return (i);
}


 cl_float3 get_float3(xmlNode *current)
{
  cl_float3 fl;
  fl.x = get_float_xml("x",current);
  fl.y = get_float_xml("y",current);
  fl.z = get_float_xml("z",current);
  return (fl);
}


cl_float4 get_float4(xmlNode *current)
{
  cl_float3 fl;
  fl.x = get_float_xml("x",current);
  fl.y = get_float_xml("y",current);
  fl.z = get_float_xml("z",current);
  fl.w = get_float_xml("w",current);
  return (fl);
}

t_color get_color(xmlNode *current)
{
  t_color col;

  col.r = get_uchar_xml("R",current);
  col.g = get_uchar_xml("B",current);;
  col.b = get_uchar_xml("V",current);;
  col.a = get_uchar_xml("T",current);;

  return (col);
}


cl_float2 get_fov(xmlNode *current)
{
  cl_float2 fov;


  fov.x = get_float_xml("fov_x",current);
  fov.y = get_float_xml("fov_y",current);
  return (fov);
}


cl_float3 get_light_fac(xmlNode *current)
{
  cl_float3 i;

  i.x = get_float_xml("amb",current);
  i.y = get_float_xml("dif",current);
  i.z = get_float_xml("spec",current);

  return (i);
}

cl_float get_rad (xmlNode *current)
{

  cl_float rad;

  rad = get_float_xml("rad",current);;
  return (rad);
}

cl_float get_ang(xmlNode *current)
{

  cl_float angle;

  angle = get_float_xml("angle",current);
  return(angle);
}


cl_float get_dis(xmlNode *current)
{

  cl_float dis;

  dis = get_float_xml("dis",current);
  return(dis);
}

cl_uint get_w(xmlNode *current)
{

  cl_uint w;

  w = get_uint_xml("W",current);
  return(w);
}

cl_uint get_h(xmlNode *current)
{

  cl_uint h;

  
  h = get_uint_xml("H",current);
  return(h);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void    pars_sphere_anex(int * tab, xmlNode *current, t_obj *new_obj)
{
  if (ft_strcmp((char*)current->name,"pos")== 0)
  {
    new_obj->pos = get_float3(current);
    tab[0] = 1;
  }
  else if (ft_strcmp((char*)current->name,"rot")== 0)
  {
    new_obj->rot = get_float3(current);
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
  else if (ft_strcmp((char*)current->name,"ref")== 0)
  {
    new_obj->ref = get_float4(current);
    tab[4] = 1;
  }
  else
    exit (0);
}


int pars_sphere( xmlNode* current, t_obj *new_obj)
{
int tab[5] = {0};
int i;

  i = 0;
  new_obj->type = SPHERE;
  //ft_bzero((void*)tab,3);
  if(!(current = current->children))
    return (-1);
  while (ztab(tab,5)==0)
  {
  // //// printf("%d\n",i);
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
//// printf("sphere ok\n");

  return (0);

}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void   pars_pave_anex(int * tab, xmlNode *current, t_obj *new_obj)
{
  if (ft_strcmp((char*)current->name,"pos")== 0)
  {
    new_obj->pos = get_float3(current);
    tab[0] = 1;
  }
  else if (ft_strcmp((char*)current->name,"rot")== 0)
  {
    new_obj->rot = get_float3(current);
    tab[1] = 1;
  }
  else if (ft_strcmp((char*)current->name,"col")== 0)
  {
    new_obj->col = get_color(current);
    tab[2] = 1;
  }
  else if (ft_strcmp((char*)current->name,"size")== 0)
  {
    new_obj->obj.pave.size = get_float3(current);
    tab[3] = 1;
  }
  else if (ft_strcmp((char*)current->name,"ref")== 0)
  {
    new_obj->ref = get_float4(current);
    tab[4] = 1;
  }
  else
    exit (0);
  //return(tab);

}

int pars_pave( xmlNode* current, t_obj *new_obj)
{
int tab[5] = {0};
int i;

  i = 0;
  new_obj->type = PAVE;
  //ft_bzero((void*)tab,3);
  if(!(current = current->children))
    return (-1);
  while (ztab(tab,5)==0)
  {
  //  //// printf("%d\n",i);
    if (i == 0)
    {
      if (!(current = current->next))
        return (-1);
    }
    else
      if(!(current = current->next->next))
        return (- 1);
  pars_pave_anex(tab,current,new_obj);
  ////// printf("%d %d %d %d\n",tab[0],tab[1],tab[2],tab[3]);
  i++;
}
//// printf("pave ok\n");

  return(0);
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void   pars_plan_anex(int *tab, xmlNode *current, t_obj *new_obj)
{
  if (ft_strcmp((char*)current->name,"pos")== 0)
  {
    new_obj->pos = get_float3(current);
    tab[0] = 1;
  }
  else if (ft_strcmp((char*)current->name,"rot")== 0)
  {
    new_obj->rot = get_float3(current);
    tab[1] = 1;
  }
  else if (ft_strcmp((char*)current->name,"col")== 0)
  {
    new_obj->col = get_color(current);
    tab[2] = 1;
  }
  else if (ft_strcmp((char*)current->name,"norm")== 0)
  {
    new_obj->obj.plan.norm = get_float3(current);
    tab[3] = 1;
  }
  else if (ft_strcmp((char*)current->name,"ref")== 0)
  {
    new_obj->ref = get_float4(current);
    tab[4] = 1;
  }
  else
    exit (0);
}

int pars_plan( xmlNode* current, t_obj *new_obj)
{ 

int tab[5] = {0};
int i;

  i = 0;
  new_obj->type = PLAN;
  //ft_bzero((void*)tab,3);
  if(!(current = current->children))
    return (-1);
  while (ztab(tab,5)==0)
  {
  //  //// printf("%d\n",i);
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
//// printf("plan ok\n");

  return(0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void   pars_cone_anex2(int *tab, xmlNode *current, t_obj *new_obj,int find)
{
  if (find == 1)
    return ;
  else if (ft_strcmp((char*)current->name,"norm")== 0)
  {
    new_obj->obj.cone.norm = get_float3(current);
    tab[3] = 1;
  }
  else if (ft_strcmp((char*)current->name,"angle")== 0)
  {
    new_obj->obj.cone.angle =  get_ang(current);
    tab[4] = 1;
  }
  else if (ft_strcmp((char*)current->name,"ref")== 0)
  {
    new_obj->ref = get_float4(current);
    tab[5] = 1;
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
    new_obj->pos = get_float3(current);
    tab[0] = 1;
    find = 1;
  }
  else if (ft_strcmp((char*)current->name,"rot")== 0)
  {
    new_obj->rot = get_float3(current);
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
  int tab[6] = {0};
  int i;

  i = 0;
  new_obj->type = CONE;
  //ft_bzero((void*)tab,3);
  if(!(current = current->children))
    return (-1);
  while (ztab(tab,6)==0)
  {
  //  //// printf("%d\n",i);
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
//// printf("cone ok\n");

  return(0);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



void   pars_cylinder_anex2(int *tab, xmlNode *current, t_obj *new_obj, int find)
{
  if (find == 1)
    return ;
  else if (ft_strcmp((char*)current->name,"norm")== 0)
  {
    new_obj->obj.cylinder.norm = get_float3(current);
    tab[3] = 1;
  }

  else if (ft_strcmp((char*)current->name,"rad")== 0)
  {
    new_obj->obj.cylinder.rad = get_rad(current); 
    tab[4] = 1;
  }
  else if (ft_strcmp((char*)current->name,"ref")== 0)
  {
    new_obj->ref = get_float4(current);
    tab[5] = 1;
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
    new_obj->pos = get_float3(current);
    tab[0] = 1;
    find = 1;
  }

  else if (ft_strcmp((char*)current->name,"rot")== 0)
  {
    new_obj->rot = get_float3(current);
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

   int tab[6] = {0};
  int i;

  i = 0;
  new_obj->type = CYLINDER;
  //ft_bzero((void*)tab,3);
  if(!(current = current->children))
    return (-1);
  while (ztab(tab,6)==0)
  {
  //  //// printf("%d\n",i);
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
//// printf("cylindeur ok\n");
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
    else if (ft_strcmp((char*)current->name,"export") == 0)
    {
      if(!(new_cam->output = (char*)xmlGetProp(current,(const xmlChar*)"PATH")))
        exit(0);
      //// printf("path in pars = %s \n",new_cam->output);
      find = 1;
      tab[7] = 1; 
    }
    pars_cam_anex3(tab,current,new_cam,find);
}


void   pars_cam_anex(int *tab, xmlNode *current, t_cam *new_cam)
{
  int find;

  find = 0;

    if (ft_strcmp((char*)current->name,"pos")== 0)
    {
      new_cam->pos = get_float3(current); ////// printf( "   pos_z %f\n",new_cam->pos.z);
      tab[0] = 1;
    find = 1;
    }
    else if (ft_strcmp((char*)current->name,"dir")== 0)
    {
      new_cam->dir =  get_float3(current);
      tab[1] = 1;
    find = 1;
    }
    else if (ft_strcmp((char*)current->name,"rot")== 0)
    {
      new_cam->rot = get_float3(current);
      tab[2] = 1;
    find = 1;
    }
    pars_cam_anex2(tab,current,new_cam,find);
}

int pars_cam( xmlNode* current, t_cam *new_cam)
{ 
  int tab[8] = {0};
  int i;

  i = 0;
  //ft_bzero((void*)tab,3);
  if(!(current = current->children))
    return (-1);
  while (ztab(tab,8)==0)
  {
  //  //// printf("%d\n",i);
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
  //// printf("cam\n");

  return(0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



void   pars_light_anex(int *tab, xmlNode *current, t_light *new_light)
{
    if(ft_strcmp((char*)current->name,"pos")== 0)
    {
      new_light->pos = get_float3(current);
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
  while (ztab(tab,3) == 0)
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
    //// printf("fuck\n");
    i++;
  }
  //// printf("light\n");

  return (0);
}


int pars_content( xmlNode* root, t_env *e)
{
//-----------------------------------Test for prefab----------------------------------
// t_prefab *tmp;
// tmp  = e->pref;
//------------------------------------------------------------------------------------
  t_obj  new_obj;
  t_cam  new_cam;
  t_light new_light;

  xmlNode* current = NULL;
  current = root;
  while (current != NULL)
  { 
      //// printf( "bonjours\n");

     if ( current->type==XML_ELEMENT_NODE ) // sert a quoi
     {
      if (ft_strcmp((char*)current->name,"sphere")== 0)
     {
       if(pars_sphere(current, &new_obj) == -1)
          return (-1);
        ft_lstadd(&e->obj, ft_lstnew(&new_obj, sizeof(t_obj)));
        //// printf("rad sph  = %f \n", new_obj.obj.sphere.rad);
     }
     else if (ft_strcmp((char*)current->name,"pave")== 0)
     {
       if(pars_pave(current, &new_obj) == -1)
         return (-1);
       ft_lstadd(&e->obj, ft_lstnew(&new_obj, sizeof(t_obj)));
    }
    else if (ft_strcmp((char*)current->name,"plan")== 0)
    {
      if(pars_plan(current, &new_obj) == -1)
        return (-1);
      ft_lstadd(&e->obj, ft_lstnew(&new_obj, sizeof(t_obj)));
    }
    else if (ft_strcmp((char*)current->name,"cone")== 0)
    {
      if(pars_cone(current, &new_obj) == -1)
        return (-1);
      ft_lstadd(&e->obj, ft_lstnew(&new_obj, sizeof(t_obj)));

    }
    else if (ft_strcmp((char*)current->name,"cylinder")== 0)
    {
      if(pars_cylinder(current, &new_obj) == -1)
        return (-1);
      ft_lstadd(&e->obj, ft_lstnew(&new_obj, sizeof(t_obj)));

    }
    else if (ft_strcmp((char*)current->name,"cam")== 0)
    {
      if(pars_cam(current, &new_cam) == -1)
        return (-1);
      ft_lstadd(&e->cam, ft_lstnew(&new_cam, sizeof(t_cam)));

    }
    else if (ft_strcmp((char*)current->name,"light") == 0)
    {
      if(pars_light(current, &new_light) == -1)
        return (-1);
      ft_lstadd(&e->light, ft_lstnew(&new_light, sizeof(t_light)));
    }
    else if (e->pref != NULL)
      ft_add_modifier_to_prefab(e,current);
  }
    current = current->next;
  }
  return (0);
}

int parsing(char *file, t_env *e)
{

  xmlDoc*  doc  = NULL;
  xmlNode* root = NULL;
  e->pref = NULL;

  doc = xmlReadFile( file, NULL, 0 );

  if ( doc==NULL )
    return -1;

  root = xmlDocGetRootElement( doc );

  if (ft_strcmp((char*)root->name, "scene") != 0)
      return (-1);
  if((root = root->children))
  {
      if(!(root = root->next))
        return (-1);
  }
  else 
    return (-1);

  if (ft_strcmp((char*)root->name, "Include") == 0)
  {
    // printf("have include\n");
    if (ft_inc_prefab(root,e) == -1)
      return (-1);
    root = root->next;
  }
  if (pars_content( root, e )== -1)
    return (-1);

  xmlFreeDoc( doc );

 xmlCleanupParser();
//// printf("end of pars\n");
  return 0;
}

// ! posible seg si une balise se glisse entre scene et le reste en totalitée

