/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/20 16:42:34 by pribault          #+#    #+#             */
/*   Updated: 2017/08/22 15:49:27 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# include <mlx.h>
# include <OpenCL/cl.h>
# include "libxml/parser.h"
# include "libxml/tree.h"
# include "libft.h"
# include "objects.h"

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
	cl_uint16	w;
	cl_uint16	h;
}				t_win;

typedef struct	s_env
{
	t_win		win;
	t_list		*obj;
	t_list		*cam;
	t_list		*light;
}				t_env;

void	parser(t_env *env, char *file);

#endif
