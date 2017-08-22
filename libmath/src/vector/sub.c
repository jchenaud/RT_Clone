/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/13 11:40:28 by pribault          #+#    #+#             */
/*   Updated: 2017/08/22 17:10:25 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmath.h"

t_vec2	sub_vec2(t_vec2 a, t_vec2 b)
{
	t_vec2	new;

	ft_bzero(&new, sizeof(t_vec2));
	new.x = a.x - b.x;
	new.y = a.y - b.y;
	return (new);
}

t_vec3	sub_vec3(t_vec3 a, t_vec3 b)
{
	t_vec3	new;

	ft_bzero(&new, sizeof(t_vec3));
	new.x = a.x - b.x;
	new.y = a.y - b.y;
	new.z = a.z - b.z;
	return (new);
}

t_vec4	sub_vec4(t_vec4 a, t_vec4 b)
{
	t_vec4	new;

	ft_bzero(&new, sizeof(t_vec4));
	new.x = a.x - b.x;
	new.y = a.y - b.y;
	new.z = a.z - b.z;
	new.w = a.w - b.w;
	return (new);
}
