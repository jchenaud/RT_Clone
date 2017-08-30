/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/20 16:42:34 by pribault          #+#    #+#             */
/*   Updated: 2017/08/30 02:21:09 by pribault         ###   ########.fr       */
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

/*
**	type: 7 bits for the object, the last for hitbox type
*/

# define SPHERE		1
# define CONE		2
# define PLAN		3
# define CYLINDER	4
# define PAVE		5

# define HITBOX		1
# define HITMODE	2

# define PRINT_KEYS	1
# define DEBUG_MODE	2

# define WIN_RATIO	9/16

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
	t_uchar		antialias_level;
	t_list		*obj;
	t_list		*cam;
	t_list		*light;
	t_uint		i;
	t_uint		n;
	t_img		*img;
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

void			init_opencl(t_cl *cl);

void			keys(t_env *env, SDL_Event *event);

void			launch_kernel(t_env *env);

void			resize_images(t_env *env);

void			antialiase(t_uchar antialias, t_cl *cl, t_img *img);

int				loop(t_env *env);

#endif
