/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/13 15:30:00 by pribault          #+#    #+#             */
/*   Updated: 2017/08/22 16:45:12 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmath.h"

void	debug_vec2(t_vec2 *vec)
{
	vec->x = (isnan(vec->x)) ? 0 : vec->x;
	vec->y = (isnan(vec->y)) ? 0 : vec->y;
}

void	debug_vec3(t_vec3 *vec)
{
	vec->x = (isnan(vec->x)) ? 0 : vec->x;
	vec->y = (isnan(vec->y)) ? 0 : vec->y;
	vec->z = (isnan(vec->z)) ? 0 : vec->z;
}

void	debug_vec4(t_vec4 *vec)
{
	vec->x = (isnan(vec->x)) ? 0 : vec->x;
	vec->y = (isnan(vec->y)) ? 0 : vec->y;
	vec->z = (isnan(vec->z)) ? 0 : vec->z;
	vec->w = (isnan(vec->w)) ? 0 : vec->w;
}
