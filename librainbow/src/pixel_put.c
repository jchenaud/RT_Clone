/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_put.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/27 19:07:04 by pribault          #+#    #+#             */
/*   Updated: 2017/08/29 23:13:32 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "librainbow.h"

void	pixel_put(t_img *img, t_pixel *p)
{
	if (p->pos.x < 0 || p->pos.x > 1 || p->pos.y < 0 || p->pos.y > 1)
		return ;
	((t_color*)img->pixels)[(int)((img->h - 1) * p->pos.y) * img->w +
	(int)((img->w - 1) * p->pos.x)] = p->color;
}
