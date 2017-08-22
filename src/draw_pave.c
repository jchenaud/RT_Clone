/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_pave.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piquerue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/22 17:23:26 by piquerue          #+#    #+#             */
/*   Updated: 2017/08/22 17:49:29 by piquerue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# define get_hit_minx(x) x->hitbox.r_min.x
# define get_hit_miny(x) x->hitbox.r_min.y
# define get_hit_minz(x) x->hitbox.r_min.z
# define get_hit_maxx(x) x->hitbox.r_max.x
# define get_hit_maxy(x) x->hitbox.r_max.y
# define get_hit_maxz(x) x->hitbox.r_max.z

int		hit_pave(t_obj *obj, cl_float3 ray)
{
	if (ray.x >= get_hit_minx(obj) && ray.x <= get_hit_maxx(obj))
		if (ray.x >= get_hit_miny(obj) && ray.x <= get_hit_maxy(obj))
			if (ray.x >= get_hit_minz(obj) && ray.x <= get_hit_maxz(obj))
				return (1);
	return (0);
}

int		hit_sphere(t_obj *obj, cl_float3 ray)
{
	return (0);
}

int		hit_cone(t_obj *obj, cl_float3 ray)
{
	return (0);
}

int		hit_plan(t_obj *obj, cl_float3 ray)
{
	return (0);
}

int		hit_cylinder(t_obj *obj, cl_float3 ray)
{
	return (0);
}

int		hit_forme(t_obj *obj, cl_float3 ray)
{
	if (obj->type == SPHERE)
		return (hit_sphere(obj, ray));
	else if (obj->type == CONE)
		return (hit_cone(obj, ray));
	else if (obj->type == PLAN)
		return (hit_plan(obj, ray));
	else if (obj->type == CYLINDER)
		return (hit_cylindre(obj, ray));
	else if (obj->type == PAVE)
		return (hit_pave(obj, ray));
	else
		return (0);
}
