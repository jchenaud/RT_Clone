/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/16 11:07:35 by pribault          #+#    #+#             */
/*   Updated: 2017/09/16 11:14:42 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmath.h"

static void	rotate(t_type *x, t_type *y, t_type angle)
{
	t_type	tmp_x;
	t_type	c;
	t_type	s;

	tmp_x = *x;
	c = cos(angle);
	s = sin(angle);
	*x = tmp_x * c - *y * s;
	*y = tmp_x * s + *y * c;
}

void	rotate_vec2(t_vec2 *vec, t_type angle)
{
	rotate(&vec->x, &vec->y, angle);
}

void	rotate_vec3(t_vec3 *vec, t_vec3 angle)
{
	rotate(&vec->x, &vec->y, angle.z);
	rotate(&vec->x, &vec->z, angle.y);
	rotate(&vec->y, &vec->z, angle.x);
}
