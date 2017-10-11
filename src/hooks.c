/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/22 18:42:46 by pribault          #+#    #+#             */
/*   Updated: 2017/10/09 13:12:07 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	normal_keys(t_env *env, SDL_Event *event)
{
	if (event->type == SDL_KEYDOWN)
	{
		if (event->key.keysym.sym == SDLK_PAGEDOWN)
			env->i = (env->i) ? env->i - 1 : env->n - 1;
		else if (event->key.keysym.sym == SDLK_PAGEUP)
			env->i = (env->i + 1) % env->n;
		render_texture(env->win->render, env->img[env->i]);
	}
}

void	preview_keys_2(t_env *env, SDL_Event *event, t_cam *cam)
{
	if (event->key.keysym.sym == SDLK_SPACE)
		move(&cam->pos, new_vec3(0, 0, 1), env->step);
	else if (event->key.keysym.sym == SDLK_LSHIFT)
		move(&cam->pos, new_vec3(0, 0, -1), env->step);
	else if (event->key.keysym.sym == SDLK_LEFT)
		cam->rot.z -= env->rot_angle;
	else if (event->key.keysym.sym == SDLK_RIGHT)
		cam->rot.z += env->rot_angle;
	else if (event->key.keysym.sym == SDLK_UP)
		cam->rot = add_vec3(cam->rot, new_vec3(env->rot_angle *
		sin(cam->rot.z), env->rot_angle * cos(cam->rot.z), 0));
	else if (event->key.keysym.sym == SDLK_DOWN)
		cam->rot = sub_vec3(cam->rot, new_vec3(env->rot_angle *
		sin(cam->rot.z), env->rot_angle * cos(cam->rot.z), 0));
	else if (event->key.keysym.sym == SDLK_KP_PLUS)
		env->step *= 2;
	else if (event->key.keysym.sym == SDLK_KP_MINUS)
		env->step /= 2;
}

void	preview_keys(t_env *env, SDL_Event *event)
{
	cl_float3	dir;
	t_cam		*cam;

	cam = get_list_n(env->cam, env->n - env->i - 1)->content;
	dir = cam->dir;
	rotate_vec3(&dir, cam->rot);
	if (event->type == SDL_KEYDOWN)
	{
		if (event->key.keysym.sym == SDLK_PAGEDOWN)
			env->i = (env->i) ? env->i - 1 : env->n - 1;
		else if (event->key.keysym.sym == SDLK_PAGEUP)
			env->i = (env->i + 1) % env->n;
		else if (event->key.keysym.sym == SDLK_w)
			move(&cam->pos, new_vec3(dir.x, dir.y, 0), env->step);
		else if (event->key.keysym.sym == SDLK_s)
			move(&cam->pos, new_vec3(-dir.x, -dir.y, 0), env->step);
		else if (event->key.keysym.sym == SDLK_a)
			move(&cam->pos, new_vec3(dir.y, -dir.x, 0), env->step);
		else if (event->key.keysym.sym == SDLK_d)
			move(&cam->pos, new_vec3(-dir.y, dir.x, 0), env->step);
		else
			preview_keys_2(env, event, cam);
		render_preview(env, get_list_n(env->cam, env->n - env->i - 1)->content,
		env->preview);
	}
}

void	render_texture(SDL_Renderer *renderer, SDL_Texture *texture)
{
	SDL_RenderCopy(renderer, texture, NULL, NULL);
	SDL_RenderPresent(renderer);
}

void	keys(t_env *env, SDL_Event *event)
{
	if (event->type == SDL_QUIT || (event->type == SDL_KEYDOWN &&
	event->key.keysym.sym == SDLK_ESCAPE))
		exit(0);
	if (event->type == SDL_WINDOWEVENT &&
	event->window.event == SDL_WINDOWEVENT_RESIZED)
	{
		SDL_SetWindowSize(env->win->win, event->window.data1,
		event->window.data1 * WIN_RATIO);
		SDL_GetWindowSize(env->win->win, &env->win->w, &env->win->h);
		resize_img(&env->preview, env->win->w, env->win->h);
	}
	else if (event->type == SDL_KEYDOWN && event->key.keysym.sym ==
	SDLK_RETURN)
	{
		env->opt += (env->opt & PREVIEW) ? -PREVIEW : PREVIEW;
		if (env->opt & PREVIEW)
			render_preview(env, get_list_n(env->cam, env->i)->content,
			env->preview);
		else
			render_texture(env->win->render, env->img[env->n - env->i - 1]);
	}
	if (env->opt & PREVIEW)
		preview_keys(env, event);
	else
		normal_keys(env, event);
}
