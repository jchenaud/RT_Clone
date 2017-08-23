/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/20 16:42:34 by pribault          #+#    #+#             */
/*   Updated: 2017/08/23 13:22:34 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# include <mlx.h>
# include "libxml/parser.h"
# include "libxml/tree.h"
# include "libft.h"
# include "objects.h"
# include "cl_struct.h"

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

# define GET_SPHERE(x)		x.obj.sphere
# define GET_PLAN(x)		x.obj.plan
# define GET_PAVE(x)		x.obj.pave
# define GET_CONE(x)		x.obj.cone
# define GET_CYLINDER(x)	x.obj.cylinder

typedef struct	s_win
{
	void		*mlx;
	void		*win;
	char		*name;
	t_uint16	w;
	t_uint16	h;
}				t_win;

/*
**	file is the .xml to open
*/

typedef struct	s_env
{
	t_cl		cl;
	t_win		win;
	char		*file;
	t_uchar		opt;
	t_list		*obj;
	t_list		*cam;
	t_list		*light;
}				t_env;

/*
**	error:
**	- error: error code
**	- state: 1=exit 0=continue
**	- param: param needed for print complete error
*/

void			error(int error, char state, void *param);

void			get_flags(t_env *env, int argc, char **argv);

void			init_opencl(t_cl *cl);
void			create_window(t_env *env, t_win *win);
t_img			*new_img(t_win *win, int w, int h);

void			key_pressed(int k, t_env *env);
void			key_released(int k, t_env *env);

void			loop(t_env *env);

#endif
