/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/07 07:21:00 by pribault          #+#    #+#             */
/*   Updated: 2017/09/15 07:36:47 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

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

void		render_image(t_cl *cl, t_cam *cam, size_t p)
{
	cl_mem	img_mem;
	cl_mem	i_mem;
	size_t	i;
	size_t	n;

	img_mem = create_buffer(cl, CL_MEM_COPY_HOST_PTR,
	sizeof(t_color) * cam->w * cam->h, cam->img->pixels);
	set_kernel_arg(&cl->render_img, &img_mem, 0);
	set_args(cl, p);
	n = cam->w * cam->h;
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
	sizeof(t_color) * cam->w * cam->h);
	delete_buffer(img_mem);
}

void		initialize_intersecs(t_env *env, t_cam *cam)
{
	t_intersec			*buffer;
	static t_intersec	def = {-1, 0};
	t_uint				i;

	i = 0;
	if (!(buffer = (t_intersec*)malloc(sizeof(t_intersec) * cam->w * cam->h)))
		error(1, 1, NULL);
	while (i < cam->w * cam->h)
		buffer[i++] = def;
	env->cl.intersecs = create_buffer(&env->cl, CL_MEM_COPY_HOST_PTR,
	sizeof(t_intersec) * cam->w * cam->h, buffer);
	free(buffer);
}

/*
**	params[0]: intersections
**	params[1]: rays
*/

void		draw_image(t_env *env, t_cam *cam, size_t m, size_t max)
{
	size_t	p;
	t_uchar	i;

	i = 0;
	initialize_intersecs(env, cam);
	create_cam_rays(env, cam, m, max);
	while (i < env->iterations)
	{
		p = cam->w * cam->h * pow(2, i);
		calculate_intersections(env, p);
		render_image(&env->cl, cam, pow(2, i));
		calculate_rays(&env->cl, p);
		i++;
	}
	delete_buffer(env->cl.intersecs);
	delete_buffer(env->cl.rays);
}

double		get_speed(void)
{
	static struct timeval	prev;
	static size_t			i = 10;
	static double			ret;
	struct timeval			t;

	if (i >= 10)
	{
		gettimeofday(&t, NULL);
		ret = ((t.tv_usec - prev.tv_usec) + (t.tv_sec - prev.tv_sec) * 1000000)
		/ (double)1000000;
		ret /= 10;
		prev = t;
		i = 0;
	}
	i++;
	return ((ret > 100) ? 0 : ret);
}

void		dispatch_rays(t_env *env, t_cam *cam)
{
	t_uint128	size;
	size_t		n;
	size_t		i;
	void		*tmp;
	double		t;

	size = cam->w * cam->h * (sizeof(t_color) +
	(size_t)pow(2, env->iterations) *
	(sizeof(t_ray) + sizeof(t_intersec))) - env->cl.textures_size -
	env->cl.n_obj * sizeof(t_obj) + env->cl.n_light * sizeof(t_light);
	n = size / env->cl.mem_size + 1;
	n = cam->h / (cam->h / n);
	i = 0;
	tmp = cam->img->pixels;
	cam->h /= n;
	while (i < n)
	{
		t = (n - i) * get_speed();
		ft_printf("\033[1A\033[0K%u/%u remaining: %.2u:%.2u:%.2u\n",
		i, n, (size_t)(t) / 3600, ((size_t)t % 3600) / 60, (size_t)t % 60);
		draw_image(env, cam, i++, n);
		cam->img->pixels += (cam->w * cam->h * sizeof(t_color));
	}
	cam->img->pixels = tmp;
	cam->h *= n;
}
