/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchenaud <jchenaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/30 21:50:55 by jchenaud          #+#    #+#             */
/*   Updated: 2017/09/02 02:14:00 by jchenaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "button.h"

/*
**	type: change laparence du bouton
*/

t_button	change_button_one_mouse(t_button b, SDL_Event event)
{
	if (mouse_are_one_button(b, event) == 0)
		b.button_draw = 1;
	else
		b.button_draw = 2;
	return (b);
}

t_button	change_button_one_click(t_button b, SDL_Event event)
{
	if (mouse_are_one_button_and_click(b, event) == 0)
	{
		if (b.button_draw == 1)
			b.button_draw = 2;
		else if (b.button_draw == 2)
			b.button_draw = 1;
	}
	return (b);
}

t_button	replace_button(t_button b, int x, int y)
{
	b.pos.x = x;
	b.pos.y = y;
	return (b);
}

t_button	change_button_size(t_button b, int h, int w)
{
	b.pos.h = h;
	b.pos.w = w;
	return (b);
}

/*
**	 permet dexcuter une autre fonction quand on click sur le bouton
*/

void		button_click(t_button b, SDL_Event event,
				void (*f)(void*), void *data)
{
	if (mouse_are_one_button_and_click(b, event) == 0)
		f(data);
}
