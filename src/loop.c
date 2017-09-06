/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/22 18:46:43 by pribault          #+#    #+#             */
/*   Updated: 2017/09/06 10:26:26 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	create_buffers(t_cl *cl)
{
	cl->n_obj_mem = clCreateBuffer(cl->context, CL_MEM_COPY_HOST_PTR,
	sizeof(t_uint), &cl->n_obj, &cl->error);
	if (cl->error != CL_SUCCESS)
		error(48, 1, &cl->error);
	cl->obj_mem = clCreateBuffer(cl->context, CL_MEM_COPY_HOST_PTR,
	cl->n_obj * sizeof(t_obj), cl->obj, &cl->error);
	if (cl->error != CL_SUCCESS)
		error(48, 1, &cl->error);
	cl->n_light_mem = clCreateBuffer(cl->context, CL_MEM_COPY_HOST_PTR,
	sizeof(t_uint), &cl->n_light, &cl->error);
	if (cl->error != CL_SUCCESS)
		error(48, 1, &cl->error);
	cl->light_mem = clCreateBuffer(cl->context, CL_MEM_COPY_HOST_PTR,
	cl->n_light * sizeof(t_light), cl->light, &cl->error);
	if (cl->error != CL_SUCCESS)
		error(48, 1, &cl->error);
}

void		render_image(t_cl *cl, t_cam *cam, void *params[2], size_t p)
{
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
	while (i < env->iterations)
	{
		p = cam->w * cam->h * pow(2, i);
		params[0] = calculate_intersections(env, p);
		render_image(&env->cl, cam, params, p);
		params[1] = calculate_rays(&env->cl, params[1], params[0], p);
		free(params[0]);
		i++;
	}
	free(params[1]);
}

void		launch_kernel(t_env *env)
{
	t_list	*cams;
	t_cam	*cam;

	if (!env->cl.n_obj || !env->cl.n_light)
		error((!env->cl.n_obj) ? 50 : 51, 1, NULL);
	cams = env->cam;
	create_buffers(&env->cl);
	while (cams)
	{
		cam = (t_cam*)cams->content;
		draw_image(env, cam);
		antialiase(env->antialias_level, &env->cl, cam->img);
		cams = cams->next;
	}
}

int			loop(t_env *env)
{
	SDL_Texture	*texture;

	while (1)
	{
		while (SDL_PollEvent(&env->win->events))
			keys(env, &env->win->events);
		if (env->i < env->n)
		{
			texture = SDL_CreateTextureFromSurface(env->win->render,
			&env->img[env->i]);
			SDL_RenderCopy(env->win->render, texture, NULL, NULL);
			SDL_DestroyTexture(texture);
		}
		SDL_RenderPresent(env->win->render);
	}
	return (0);
}
