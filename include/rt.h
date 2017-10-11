/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/20 16:42:34 by pribault          #+#    #+#             */
/*   Updated: 2017/10/09 19:25:50 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# include "libxml/parser.h"
# include "libxml/tree.h"
# include "libft.h"
# include "objects.h"
# include "cl_struct.h"
# include "librainbow.h"
# include <sys/time.h>

/*
**	type: 7 bits for the object, the last for hitbox type
*/

# define SPHERE		1
# define CONE		2
# define PLAN		3
# define CYLINDER	4
# define PAVE		5
# define TRIANGLE	6

# define HITBOX		1
# define HITMODE	2

# define VISIBLE	0
# define INVISIBLE	1

# define PARALLELE	1

# define PRINT_KEYS	0x1
# define DEBUG_MODE	0x2
# define PREVIEW	0x4
# define DEGREES	0x8

# define WIN_RATIO	9/16

# define PI			3.1415926535

# define GET_SPHERE(x)		x.obj.sphere
# define GET_PLAN(x)		x.obj.plan
# define GET_PAVE(x)		x.obj.pave
# define GET_CONE(x)		x.obj.cone
# define GET_CYLINDER(x)	x.obj.cylinder

/*
**	file is the .xml to open
*/

typedef struct	s_env
{
	t_cl		cl;
	t_win		*win;
	char		*file;
	t_uchar		opt;
	t_uchar		iterations;
	t_uchar		antialias_level;
	t_list		*obj;
	t_list		*cam;
	t_list		*light;
	t_prefab	*pref;
	t_prefab	*pf_o;
	t_vector	*textures;
	t_uint		i;
	t_uint		n;
	SDL_Texture	**img;
	t_img		*icone;
	t_img		*preview;
	int			find_cam_light;
	float		step;
	float		rot_angle;
}				t_env;

/*
**	error:
**	- error: error code
**	- state: 1=exit 0=continue
**	- param: param needed for print complete error
*/

void			error(int error, char state, void *param);
int				parsing(char *file, t_env *e);

void			get_flags(t_env *env, int argc, char **argv);

void			convert_to_radians(t_obj *obj, t_uint n);
void			convert_rotations_to_normals(t_obj *obj, t_uint n);
void			allocate_textures(t_env *env);
void			alloc_images(t_list *cam);
void			init_opencl(t_cl *cl);
cl_mem			create_buffer(t_cl *cl, cl_mem_flags flags,
				size_t size, void *ptr);
void			set_kernel_arg(cl_kernel *kernel, cl_mem *mem, cl_uint i);
void			nd_range_kernel(t_cl *cl, cl_kernel *kernel, size_t n);
void			read_buffer(t_cl *cl, cl_mem mem, void *ptr, size_t size);
void			delete_buffer(cl_mem mem);

void			keys(t_env *env, SDL_Event *event);

void			move(cl_float3 *pos, cl_float3 dir, float step);

double			get_speed(void);
void			dispatch_rays(t_env *env, t_cam *cam);
void			create_cam_rays(t_env *env, t_cam *cam, size_t m, size_t max);
void			initialize_intersecs(t_env *env, t_cam *cam, size_t m, size_t max);
void			calculate_intersections(t_env *env, size_t n);
void			calculate_rays(t_cl *cl, size_t p);
void			launch_kernel(t_env *env);
void			render_preview(t_env *env, t_cam *cam, t_img *img);
void			render_texture(SDL_Renderer *renderer, SDL_Texture *texture);
t_list			*get_list_n(t_list *list, int n);

void			resize_images(t_env *env);

void			antialiase(t_uchar antialias, t_cl *cl, t_img *img);

int				loop(t_env *env);

void			ft_init_obj_default(t_obj *new_obj);
int				ft_inc_prefab(xmlNode *root, t_env *e);
char			*get_path_prefab(xmlNode *current);
char			*get_p_name(xmlNode *current, int i);
int				number_of_prefab(xmlNode *current);
int				ft_inc_prefab(xmlNode *root, t_env *e);
int				ft_add_modifier_to_prefab(t_env *e, xmlNode *current);

t_prefab		*are_prefab(xmlNode *current, t_prefab *tmp);
void			modi_pos(t_prefab *tmp, xmlNode *current);
int				ft_pars_prefab(t_env *e, xmlNode *current);
int				pars_triangle(xmlNode *current, t_obj *new_obj);
int				pars_cylinder(xmlNode *current, t_obj *new_obj);
int				pars_cone(xmlNode *current, t_obj *new_obj);
int				pars_plan(xmlNode *current, t_obj *new_obj);
int				pars_pave(xmlNode *current, t_obj *new_obj);
int				pars_sphere(xmlNode *current, t_obj *new_obj);
int				pars_cam(xmlNode *current, t_cam *new_cam);
int				pars_light(xmlNode *current, t_light *new_light);

void			get_box(xmlNode *current, t_obj *new_obj);
cl_float3		get_float3(xmlNode *current);
cl_float3		get_float3_normal(xmlNode *current);
cl_float4		get_float4(xmlNode *current);
cl_float		get_float_xml(char *name, xmlNode *current);
cl_uchar		get_uchar_xml(char *name, xmlNode *current);
cl_uint			get_uint_xml(char *name, xmlNode *current);

t_color			get_color(xmlNode *current);
cl_float3		get_light_fac(xmlNode *current);
void			get_texture(xmlNode *current, t_obj *new_obj);
cl_float		get_rad (xmlNode *current);
cl_float		get_ang(xmlNode *current);
cl_uint			get_w(xmlNode *current);
cl_uint			get_h(xmlNode *current);
cl_float		get_dis(xmlNode *current);
cl_float2		get_fov(xmlNode *current);

#endif
