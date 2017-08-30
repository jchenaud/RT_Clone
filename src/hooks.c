/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/22 18:42:46 by pribault          #+#    #+#             */
/*   Updated: 2017/08/30 02:37:43 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	keys(t_env *env, SDL_Event *event)
{
	if (event->type == SDL_QUIT)
		exit(0);
	if (event->type == SDL_KEYDOWN)
	{
		if (event->key.keysym.sym == SDLK_ESCAPE)
			exit(0);
	}
	else if (event->type == SDL_WINDOWEVENT)
	{
		if (event->window.event == SDL_WINDOWEVENT_RESIZED)
		{
			if (event->window.data1 < 640 || event->window.data2 < 480)
				event->window.data1 = 640;
			SDL_SetWindowSize(env->win->win, event->window.data1,
			event->window.data1 * WIN_RATIO);
		}
	}
}
