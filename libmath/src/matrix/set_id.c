/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_id.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/13 12:15:44 by pribault          #+#    #+#             */
/*   Updated: 2017/08/22 16:50:11 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmath.h"

void	set_id_mat2(t_mat2 *mat, t_type id)
{
	clean_mat2(mat);
	mat->x.x = id;
	mat->y.y = id;
}

void	set_id_mat3(t_mat3 *mat, t_type id)
{
	clean_mat3(mat);
	mat->x.x = id;
	mat->y.y = id;
	mat->z.z = id;
}

void	set_id_mat4(t_mat4 *mat, t_type id)
{
	clean_mat4(mat);
	mat->x.x = id;
	mat->y.y = id;
	mat->z.z = id;
	mat->w.w = id;
}
