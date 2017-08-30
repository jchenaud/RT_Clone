/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   private.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/27 16:56:46 by pribault          #+#    #+#             */
/*   Updated: 2017/08/29 23:12:28 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRIVATE_H
# define PRIVATE_H

# include "libft.h"
# include "types.h"
# include "libimages.h"
# include "libmath.h"
# include <sys/time.h>
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

t_win			*new_window(char *title, t_uint16 w, t_uint16 h);
void			delete_window(t_win **win);

t_uint			get_fps(void);
void			set_fps(t_uint fps);

char			*get_version(void);
t_uint16		get_width(t_win *win);
t_uint16		get_height(t_win *win);
char			*get_title(t_win *win);

t_img			*new_img(int w, int h);

void			pixel_put(t_img *img, t_pixel *p);
void			draw_line(t_img *img, t_pixel *a, t_pixel *b);

#endif
