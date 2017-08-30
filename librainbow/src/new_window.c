/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_window.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/27 16:40:23 by pribault          #+#    #+#             */
/*   Updated: 2017/08/30 01:20:44 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private.h"

t_win	*new_window(char *title, t_uint16 w, t_uint16 h)
{
	t_win	*win;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		return (NULL);
	if (!(win = (t_win*)malloc(sizeof(t_win))) ||
	!(win->win = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED,
	SDL_WINDOWPOS_CENTERED, w, h, SDL_WINDOW_RESIZABLE)) ||
	!(win->render = SDL_CreateRenderer(win->win, -1,
	0)) ||
	!(win->w = w) ||
	!(win->h = h) ||
	!(win->name = ft_strdup(title)))
		return (NULL);
	return (win);
}