/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/07 07:21:00 by pribault          #+#    #+#             */
/*   Updated: 2017/09/08 04:23:09 by pribault         ###   ########.fr       */
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
		set_kernel_arg(&cl->render_img, &i_mem, 8);
		nd_range_kernel(cl, &cl->render_img, n);
		i++;
	}
	read_buffer(cl, img_mem, cam->img->pixels,
	sizeof(t_color) * cam->w * cam->h);
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

void		draw_image(t_env *env, t_cam *cam)
{
	void	*params[2];
	size_t	p;
	t_uchar	i;

	i = 0;
	params[1] = create_cam_rays(env, cam);
	initialize_intersecs(env, cam);
	while (i < env->iterations)
	{
		p = cam->w * cam->h * pow(2, i);
		params[0] = calculate_intersections(env, p);
		render_image(&env->cl, cam, pow(2, i));
		params[1] = calculate_rays(&env->cl, params[1], params[0], p);
		free(params[0]);
		i++;
	}
	free(params[1]);
}
