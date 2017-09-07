/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/22 18:46:43 by pribault          #+#    #+#             */
/*   Updated: 2017/09/07 07:21:34 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	create_buffers(t_cl *cl)
{
	cl->n_obj_mem = create_buffer(cl, CL_MEM_COPY_HOST_PTR,
	sizeof(t_uint), &cl->n_obj);
	cl->obj_mem = create_buffer(cl, CL_MEM_COPY_HOST_PTR,
	sizeof(t_obj) * cl->n_obj, cl->obj);
	cl->n_light_mem = create_buffer(cl, CL_MEM_COPY_HOST_PTR,
	sizeof(t_uint), &cl->n_light);
	cl->light_mem = create_buffer(cl, CL_MEM_COPY_HOST_PTR,
	sizeof(t_light) * cl->n_light, cl->light);
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
