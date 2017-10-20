/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/07 07:21:00 by pribault          #+#    #+#             */
/*   Updated: 2017/10/20 15:05:55 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
**	used to set kernel arg in render_image function
*/

static void	set_args(t_cl *cl, size_t p)
{
	cl_mem	p_mem;

	p_mem = create_buffer(cl, CL_MEM_COPY_HOST_PTR, sizeof(size_t), &p);
	set_kernel_arg(&cl->render_img, &p_mem, 1);
	set_kernel_arg(&cl->render_img, &cl->rays, 2);
	set_kernel_arg(&cl->render_img, &cl->intersecs, 3);
	set_kernel_arg(&cl->render_img, &cl->n_obj_mem, 4);
	set_kernel_arg(&cl->render_img, &cl->obj_mem, 5);
	set_kernel_arg(&cl->render_img, &cl->n_light_mem, 6);
	set_kernel_arg(&cl->render_img, &cl->light_mem, 7);
	set_kernel_arg(&cl->render_img, &cl->textures_mem, 8);
}

/*
**	render a pixel for p rays.
**	each ray generate two rays, one reflected and one refracted,
**	with a big iteration one ray can finally generate 16, 32, 64 etc... rays
*/

void		render_image(t_cl *cl, t_cam *cam, size_t p, size_t max)
{
	cl_mem	img_mem;
	cl_mem	i_mem;
	size_t	i;
	size_t	n;

	img_mem = create_buffer(cl, CL_MEM_COPY_HOST_PTR,
	sizeof(t_color) * cam->w * max, cam->img->pixels);
	set_kernel_arg(&cl->render_img, &img_mem, 0);
	set_args(cl, p);
	n = cam->w * max;
	i = 0;
	while (i < p)
	{
		i_mem = create_buffer(cl, CL_MEM_COPY_HOST_PTR, sizeof(size_t), &i);
		set_kernel_arg(&cl->render_img, &i_mem, 9);
		nd_range_kernel(cl, &cl->render_img, n);
		delete_buffer(i_mem);
		i++;
	}
	read_buffer(cl, img_mem, cam->img->pixels,
	sizeof(t_color) * cam->w * max);
	delete_buffer(img_mem);
}

/*
**	iterate and render image for each iteration
*/

void		draw_image(t_env *env, t_cam *cam, size_t m, size_t max)
{
	size_t	p;
	t_uchar	i;

	i = 0;
	initialize_intersecs(env, cam, m, max);
	create_cam_rays(env, cam, m, max);
	while (i < env->iterations)
	{
		p = cam->w * ((m == max) ? cam->h % max : cam->h / max) * pow(2, i);
		calculate_intersections(env, p);
		render_image(&env->cl, cam, pow(2, i), ((m == max) ?
		cam->h % max : cam->h / max));
		calculate_rays(&env->cl, p);
		i++;
	}
	delete_buffer(env->cl.intersecs);
	delete_buffer(env->cl.rays);
}

/*
**	used to printf time remaining and number of image parts already calculated
*/

void		print_datas(size_t n, size_t i)
{
	double		t;

	t = (n - i) * get_speed();
	ft_printf("\033[1A\033[0K%u/%u remaining: %.2u:%.2u:%.2u\n",
	i, n, (size_t)(t) / 3600, ((size_t)t % 3600) / 60, (size_t)t % 60);
}

/*
**	dispatch the image in pieces if the memory required is too big
*/

void		dispatch_rays(t_env *env, t_cam *cam)
{
	t_int128	size;
	size_t		n;
	size_t		i;
	size_t		rest;
	void		*tmp;

	size = cam->w * cam->h * (sizeof(t_color) +
	(size_t)pow(2, env->iterations) *
	(sizeof(t_ray) + sizeof(t_intersec))) - env->cl.textures_size -
	env->cl.n_obj * sizeof(t_obj) - env->cl.n_light * sizeof(t_light);
	n = (size > 0) ? size / env->cl.mem_size + 1 : 1;
	i = 0;
	tmp = cam->img->pixels;
	rest = (n) ? cam->h % n : 0;
	while ((rest) ? i <= n : i < n)
	{
		print_datas(n, i);
		draw_image(env, cam, i, n);
		cam->img->pixels += (cam->w * ((i == n) ? cam->h % n : cam->h / n) *
		sizeof(t_color));
		i++;
	}
	cam->img->pixels = tmp;
}
