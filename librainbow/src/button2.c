/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchenaud <jchenaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/30 21:50:55 by jchenaud          #+#    #+#             */
/*   Updated: 2017/09/02 02:14:02 by jchenaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "button.h"

t_button	load_button(t_button b)
{
	if (!(b.b1 = IMG_Load(b.button_img1)))
		exit(0);
	if (!(b.b2 = IMG_Load(b.button_img2)))
		exit(0);
	b.bt1 = SDL_CreateTextureFromSurface(b.win->render, b.b1);
	b.bt2 = SDL_CreateTextureFromSurface(b.win->render, b.b2);
	return (b);
}

int			mouse_are_one_button(t_button b, SDL_Event event)
{
	if (event.motion.x >= b.pos.x && event.motion.x <= b.pos.x + b.pos.w &&
			event.motion.y >= b.pos.y && event.motion.y <= b.pos.y + b.pos.h)
		return (0);
	return (1);
}

int			mouse_are_one_button_and_click(t_button b, SDL_Event event)
{
	if (event.motion.x >= b.pos.x && event.motion.x <= b.pos.x + b.pos.w &&
			event.motion.y >= b.pos.y && event.motion.y <= b.pos.y + b.pos.h &&
			event.type == SDL_MOUSEBUTTONDOWN && event.button.clicks == 1)
		return (0);
	return (1);
}

/*
**	affiche les bouton cette fonction doit etre apeler pour tout affichage
*/

void		print_button(t_button b)
{
	if (b.button_draw == 2)
		SDL_RenderCopy(b.win->render, b.bt1, NULL, &b.pos);
	if (b.button_draw == 1)
		SDL_RenderCopy(b.win->render, b.bt2, NULL, &b.pos);
}

/*
**	initialise un bouton
*/

t_button	init_load_place_button(char *path1, char *path2, t_win *win)
{
	t_button b;

	b.button_img1 = path1;
	b.button_img2 = path2;
	b.win = win;
	b.button_draw = 1;
	b = load_button(b);
	b.pos.x = 0;
	b.pos.y = 0;
	b.pos.h = 100;
	b.pos.w = 100;
	return (b);
}
