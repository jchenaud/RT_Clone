/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/09 13:08:04 by pribault          #+#    #+#             */
/*   Updated: 2017/10/09 13:08:39 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	move(cl_float3 *pos, cl_float3 dir, float step)
{
	normalize_vec3(&dir);
	dir.x *= step;
	dir.y *= step;
	dir.z *= step;
	*pos = add_vec3(*pos, dir);
}
