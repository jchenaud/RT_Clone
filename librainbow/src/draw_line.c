/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/27 18:56:24 by pribault          #+#    #+#             */
/*   Updated: 2017/08/28 02:11:57 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private.h"

static void		define_color(t_pixel *a, t_pixel *b, t_pixel *i)
{
	float	r;

	r = sqrt((b->pos.x - i->pos.x) * (b->pos.x - i->pos.x) +
	(b->pos.y - i->pos.y) * (b->pos.y - i->pos.y)) /
	sqrt((b->pos.x - a->pos.x) * (b->pos.x - a->pos.x) +
	(b->pos.y - a->pos.y) * (b->pos.y - a->pos.y));
	i->color.r = r * a->color.r + (1.0 - r) * b->color.r;
	i->color.g = r * a->color.g + (1.0 - r) * b->color.g;
	i->color.b = r * a->color.b + (1.0 - r) * b->color.b;
	i->color.a = r * a->color.a + (1.0 - r) * b->color.a;
}

static void		print_pixel(t_img *img, t_pixel *a, t_pixel *b, t_pixel *i)
{
	define_color(a, b, i);
	pixel_put(img, i);
}

static t_vec2	get_diff(t_img *img)
{
	t_vec2	diff;

	diff.x = 1 / (float)img->w;
	diff.y = 1 / (float)img->h;
	return (diff);
}

void			get_function(t_pixel *a, t_pixel *b, float *c, float *d)
{
	*c = (a->pos.y - b->pos.y) / (a->pos.x - b->pos.x);
	*c = (isnan(*c)) ? 0 : *c;
	*c = (isinf(*c)) ? 2147483647 : *c;
	*d = a->pos.y - *c * a->pos.x;
}

void			draw_line(t_img *img, t_pixel *a, t_pixel *b)
{
	t_pixel	i;
	t_vec2	diff;
	float	c;
	float	d;

	get_function(a, b, &c, &d);
	diff = get_diff(img);
	i = *a;
	if (ft_fabs(c) * (img->h / (float)img->w) < 1)
		while ((a->pos.x <= b->pos.x) ?
		i.pos.x <= b->pos.x : i.pos.x >= b->pos.x)
		{
			i.pos.y = c * i.pos.x + d;
			print_pixel(img, a, b, &i);
			i.pos.x += (a->pos.x <= b->pos.x) ? diff.x : -diff.x;
		}
	else
		while ((a->pos.y <= b->pos.y) ?
		i.pos.y <= b->pos.y : i.pos.y >= b->pos.y)
		{
			i.pos.x = (i.pos.y - d) / c;
			print_pixel(img, a, b, &i);
			i.pos.y += (a->pos.y <= b->pos.y) ? diff.y : -diff.y;
		}
}
