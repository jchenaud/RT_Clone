/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/13 11:14:04 by pribault          #+#    #+#             */
/*   Updated: 2017/08/22 17:08:33 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmath.h"

t_vec2	new_vec2(t_type x, t_type y)
{
	t_vec2	new;

	ft_bzero(&new, sizeof(t_vec2));
	new.x = x;
	new.y = y;
	return (new);
}

t_vec3	new_vec3(t_type x, t_type y, t_type z)
{
	t_vec3	new;

	ft_bzero(&new, sizeof(t_vec3));
	new.x = x;
	new.y = y;
	new.z = z;
	return (new);
}

t_vec4	new_vec4(t_type x, t_type y, t_type z, t_type w)
{
	t_vec4	new;

	ft_bzero(&new, sizeof(t_vec4));
	new.x = x;
	new.y = y;
	new.z = z;
	new.w = w;
	return (new);
}
