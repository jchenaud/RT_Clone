/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_triangle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/31 03:26:56 by pribault          #+#    #+#             */
/*   Updated: 2017/08/31 03:37:32 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "librainbow.h"

static void	sort_pixels(t_pixel **a, t_pixel **b, t_pixel **c)
{
	t_pixel	*tmp;

	if ((*b)->pos.x < (*a)->pos.x)
	{
		tmp = *b;
		*b = *a;
		*a = tmp;
	}
	if ((*c)->pos.x < (*a)->pos.x)
	{
		tmp = *c;
		*c = *a;
		*a = tmp;
	}
	if ((*c)->pos.x < (*b)->pos.x)
	{
		tmp = *b;
		*b = *c;
		*c = tmp;
	}
}

static void	define_color(t_pixel *a, t_pixel *b, t_pixel *i)
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

static void	draw_triangle_part1(t_img *img, t_pixel *a, t_pixel *b, t_pixel *c)
{
	t_pixel	m[2];
	float	d[2];
	float	e[2];
	float	diff;

	diff = 1 / (float)img->w;
	d[0] = (a->pos.x != b->pos.x) ?
	(a->pos.y - b->pos.y) / (a->pos.x - b->pos.x) : 0;
	d[1] = (a->pos.x != c->pos.x) ?
	(a->pos.y - c->pos.y) / (a->pos.x - c->pos.x) : 0;
	e[0] = a->pos.y - a->pos.x * d[0];
	e[1] = a->pos.y - a->pos.x * d[1];
	m[0] = *a;
	while (m[0].pos.x <= b->pos.x)
	{
		m[1].pos.x = m[0].pos.x;
		m[0].pos.y = m[0].pos.x * d[0] + e[0];
		m[1].pos.y = m[1].pos.x * d[1] + e[1];
		define_color(a, b, &m[0]);
		define_color(a, c, &m[1]);
		draw_line(img, &m[0], &m[1]);
		m[0].pos.x += diff;
	}
}

static void	draw_triangle_part2(t_img *img, t_pixel *a, t_pixel *b, t_pixel *c)
{
	t_pixel	m[2];
	float	d[2];
	float	e[2];
	float	diff;

	diff = 1 / (float)img->w;
	d[0] = (b->pos.x != c->pos.x) ?
	(b->pos.y - c->pos.y) / (b->pos.x - c->pos.x) : 0;
	d[1] = (a->pos.x != c->pos.x) ?
	(a->pos.y - c->pos.y) / (a->pos.x - c->pos.x) : 0;
	e[0] = b->pos.y - b->pos.x * d[0];
	e[1] = a->pos.y - a->pos.x * d[1];
	m[0] = *b;
	while (m[0].pos.x <= c->pos.x)
	{
		m[1].pos.x = m[0].pos.x;
		m[0].pos.y = m[0].pos.x * d[0] + e[0];
		m[1].pos.y = m[1].pos.x * d[1] + e[1];
		define_color(b, c, &m[0]);
		define_color(a, c, &m[1]);
		draw_line(img, &m[0], &m[1]);
		m[0].pos.x += diff;
	}
}

void		draw_triangle(t_img *img, t_pixel *a, t_pixel *b, t_pixel *c)
{
	if (!a || !b || !c)
		return ;
	sort_pixels(&a, &b, &c);
	draw_triangle_part1(img, a, b, c);
	draw_triangle_part2(img, a, b, c);
}
