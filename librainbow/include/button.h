/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchenaud <jchenaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/30 22:16:24 by jchenaud          #+#    #+#             */
/*   Updated: 2017/09/02 02:25:41 by jchenaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUTTON_H
# define BUTTON_H

# include "librainbow.h"

typedef struct		s_button
{
	char			*button_img1;
	char			*button_img2;
	SDL_Rect		pos;
	int				button_draw;
	SDL_Surface		*b1;
	SDL_Surface		*b2;
	SDL_Texture		*bt1;
	SDL_Texture		*bt2;
	t_win			*win;
}					t_button;

t_button			change_button_size(t_button b, int h, int w);
t_button			replace_button(t_button b, int x, int y);

t_button			change_button_one_click(t_button b, SDL_Event event);
t_button			change_button_one_mouse(t_button b, SDL_Event event);

t_button			init_load_place_button(char *path1, char *path2,
					t_win *win);

int					mouse_are_one_button(t_button b, SDL_Event event);
int					mouse_are_one_button_and_click(t_button b,
					SDL_Event event);

t_button			load_button(t_button b);
void				print_button(t_button b);

#endif
