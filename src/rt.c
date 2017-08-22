/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/20 16:42:31 by pribault          #+#    #+#             */
/*   Updated: 2017/08/22 19:55:34 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_img	*new_img(t_win *win, int w, int h)
{
	t_img	*new;
	int		bpp;
	int		size_l;
	int		endian;

	if (!(new = (t_img*)malloc(sizeof(t_img))))
		error(1, 1, NULL);
	new->w = w;
	new->h = h;
	if (!(new->ptr = mlx_new_image(win->mlx, w, h)))
		error(34, 1, NULL);
	if (!(new->img = (t_color*)mlx_get_data_addr(new->ptr, &bpp, &size_l,
	&endian)))
		error(34, 1, NULL);
	if (bpp != 32 || endian != 0)
		error(35, 1, NULL);
	ft_printf("bpp=%d endian=%d\n", bpp, endian);
	return (new);
}

void	create_window(t_env *env, t_win *win)
{
	if (!(win->mlx = mlx_init()))
		error(32, 1, NULL);
	if (!(win->win = mlx_new_window(win->mlx, win->w, win->h, win->name)))
		error(33, 1, NULL);
	env->img = new_img(win, win->w, win->h);
	mlx_hook(win->win, 2, (1L << 0), (void*)&key_pressed, env);
	mlx_hook(win->win, 3, (1L << 1), (void*)&key_released, env);
	mlx_loop_hook(win->win, (void*)&loop, env);
}

t_env	*init_env(void)
{
	t_env	*env;

	if (!(env = (t_env*)malloc(sizeof(t_env))))
		error(1, 1, NULL);
	ft_bzero(env, sizeof(t_env));
	env->win.name = "RT";
	env->win.w = 1920;
	env->win.h = 1080;
	return (env);
}

int		main(int argc, char **argv)
{
	t_env	*env;

	if (argc == 1)
		error(0, 1, NULL);
	env = init_env();
	get_flags(env, argc, argv);
	create_window(env, &env->win);
	ft_printf("\n");
	mlx_loop(env->win.mlx);
	return (0);
}
