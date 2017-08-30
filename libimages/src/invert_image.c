/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invert_image.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/30 01:31:43 by pribault          #+#    #+#             */
/*   Updated: 2017/08/30 02:19:11 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libimages.h"
#include "private.h"

void	invert_image(t_img *img)
{
	t_color	tmp[img->w];
	int		i;

	if (!img)
		return ;
	i = 0;
	while (i < img->h / 2)
	{
		ft_memcpy(&tmp, &((t_color*)img->pixels)[i * img->w],
		sizeof(t_color) * img->w);
		ft_memcpy(&((t_color*)img->pixels)[i * img->w],
		&((t_color*)img->pixels)[(img->h - i - 1) * img->w],
		sizeof(t_color) * img->w);
		ft_memcpy(&((t_color*)img->pixels)[(img->h - i - 1) * img->w],
		&tmp, sizeof(t_color) * img->w);
		i++;
	}
}
