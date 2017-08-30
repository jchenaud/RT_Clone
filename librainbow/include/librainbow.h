/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   librainbow.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/27 16:39:15 by pribault          #+#    #+#             */
/*   Updated: 2017/08/29 23:12:32 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBRAINBOW_H
# define LIBRAINBOW_H

# include "libft.h"
# include "libimages.h"
# include "libmath.h"
# include "SDL2/SDL.h"

typedef struct		s_pixel
{
	t_vec2			pos;
	t_color			color;
}					t_pixel;

typedef struct		s_win
{
	SDL_Window		*win;
	SDL_Renderer	*render;
	SDL_Event		events;
	char			*name;
	t_uint16		w;
	t_uint16		h;
}					t_win;

void			*new_window(char *title, t_uint16 w, t_uint16 h);
void			delete_window(void **win);

t_uint			get_fps(void);
void			set_fps(t_uint fps);

char			*get_version(void);
t_uint16		get_width(void *win);
t_uint16		get_height(void *win);
char			*get_title(void *win);

t_img			*new_img(int w, int h);

void			pixel_put(t_img *img, t_pixel *p);
void			draw_line(t_img *img, t_pixel *a, t_pixel *b);

#endif
