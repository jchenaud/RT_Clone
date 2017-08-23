/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/20 16:42:31 by pribault          #+#    #+#             */
/*   Updated: 2017/08/23 13:22:50 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

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
	init_opencl(&env->cl);
	ft_printf("\n");
	mlx_loop(env->win.mlx);
	return (0);
}
