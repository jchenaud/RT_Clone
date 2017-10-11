/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize_img.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/29 15:26:47 by pribault          #+#    #+#             */
/*   Updated: 2017/09/29 15:29:48 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "librainbow.h"

void	resize_img(t_img **img, int w, int h)
{
	if (!img || !*img || ((*img)->w == w && (*img)->h == h))
		return ;
	SDL_FreeSurface(*img);
	*img = new_img(w, h);
}
