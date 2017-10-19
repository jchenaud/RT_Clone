/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_image.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/27 17:10:48 by pribault          #+#    #+#             */
/*   Updated: 2017/08/31 03:46:39 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private.h"

t_img	*new_img(int w, int h)
{
	t_img	*new;

	if (!(new = SDL_CreateRGBSurface(0, w, h, 32,
	0xff0000, 0xff00, 0xff, 0xff000000)))
		return (NULL);
	ft_bzero(new->pixels, 4 * w * h);
	return (new);
}
