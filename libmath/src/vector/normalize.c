/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/13 11:23:35 by pribault          #+#    #+#             */
/*   Updated: 2017/08/22 16:45:19 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmath.h"

void	normalize_vec2(t_vec2 *vec)
{
	t_type	norm;

	norm = sqrt(vec->x * vec->x + vec->y * vec->y);
	vec->x /= norm;
	vec->y /= norm;
}

void	normalize_vec3(t_vec3 *vec)
{
	t_type	norm;

	norm = sqrt(vec->x * vec->x + vec->y * vec->y + vec->z * vec->z);
	vec->x /= norm;
	vec->y /= norm;
	vec->z /= norm;
}

void	normalize_vec4(t_vec4 *vec)
{
	t_type	norm;

	norm = sqrt(vec->x * vec->x + vec->y * vec->y + vec->z * vec->z +
	vec->w * vec->w);
	vec->x /= norm;
	vec->y /= norm;
	vec->z /= norm;
	vec->w /= norm;
}
