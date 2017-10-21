/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modi_size_anex.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchenaud <jchenaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/21 13:45:26 by jchenaud          #+#    #+#             */
/*   Updated: 2017/10/21 13:58:16 by jchenaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	modi_size_hitbox(t_list *tl, xmlNode *current)
{
	t_vec3 hit;

	hit.x = get_float_xml("x", current);
	hit.y = get_float_xml("x", current);
	hit.z = get_float_xml("x", current);
	((t_obj*)tl->content)->pos.x *= get_float_xml("x", current);
	((t_obj*)tl->content)->pos.y *= get_float_xml("x", current);
	((t_obj*)tl->content)->pos.z *= get_float_xml("x", current);
	((t_obj*)tl->content)->hitbox.min = mult_vec3(
		((t_obj*)tl->content)->hitbox.min, hit);
	((t_obj*)tl->content)->hitbox.max = mult_vec3(
		((t_obj*)tl->content)->hitbox.max, hit);
	((t_obj*)tl->content)->hitbox.r_min = mult_vec3(
		((t_obj*)tl->content)->hitbox.r_min, hit);
	((t_obj*)tl->content)->hitbox.r_max = mult_vec3(
		((t_obj*)tl->content)->hitbox.r_max, hit);
}
