/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/13 15:33:33 by pribault          #+#    #+#             */
/*   Updated: 2017/08/22 16:49:55 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmath.h"

void	debug_mat2(t_mat2 *mat)
{
	debug_vec2(&mat->x);
	debug_vec2(&mat->y);
}

void	debug_mat3(t_mat3 *mat)
{
	debug_vec3(&mat->x);
	debug_vec3(&mat->y);
	debug_vec3(&mat->z);
}

void	debug_mat4(t_mat4 *mat)
{
	debug_vec4(&mat->x);
	debug_vec4(&mat->y);
	debug_vec4(&mat->z);
	debug_vec4(&mat->w);
}
