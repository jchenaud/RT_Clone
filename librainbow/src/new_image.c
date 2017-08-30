/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_image.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/27 17:10:48 by pribault          #+#    #+#             */
/*   Updated: 2017/08/30 01:18:23 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private.h"

t_img	*new_img(int w, int h)
{
	return (SDL_CreateRGBSurface(0, w, h, 32,
	0xff0000, 0xff00, 0xff, 0xff000000));
}