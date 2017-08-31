/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_polygone.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/31 05:22:17 by pribault          #+#    #+#             */
/*   Updated: 2017/08/31 06:05:36 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "librainbow.h"

void	draw_polygone(t_img *img, t_pixel *p, int n)
{
	int		t[3];
	int		nbr;
	int		i;

	nbr = n - 2;
	i = 0;
	t[2] = 0;
	while (i < nbr)
	{
		t[0] = t[2];
		t[1] = t[0] + t[0] / n + 1;
		t[2] = t[1] + t[1] / n + 1;
		draw_triangle(img, &p[t[0] % n], &p[t[1] % n], &p[t[2] % n]);
		i++;
	}
}
