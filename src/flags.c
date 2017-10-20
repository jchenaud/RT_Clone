/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/22 17:18:56 by pribault          #+#    #+#             */
/*   Updated: 2017/10/20 15:07:51 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
**	all those functions are used to get the flags passed to the program
*/

void	get_param4(t_env *env, int argc, char **argv, int *i)
{
	if (!ft_strcmp(argv[*i], "-filtre"))
		if (*i + 1 < argc)
			env->filtre = ft_atou(argv[++(*i)]);
		else
			error(25, 0, NULL);
	else if (!ft_strcmp(argv[*i], "-preview"))
		env->opt += (!(env->opt & PREVIEW)) ? PREVIEW : 0;
	else
		error(17, 0, argv[*i]);
}

void	get_param3(t_env *env, int argc, char **argv, int *i)
{
	if (!ft_strcmp(argv[*i], "-iterations"))
		if (*i + 1 < argc)
			env->iterations = ft_atou(argv[++(*i)]);
		else
			error(23, 0, NULL);
	else if (!ft_strcmp(argv[*i], "-angle"))
		if (*i + 1 < argc)
		{
			if (!ft_strcmp(argv[++(*i)], "radians"))
				env->opt -= (env->opt & DEGREES) ? DEGREES : 0;
			else if (!ft_strcmp(argv[*i], "degrees"))
				env->opt += (!(env->opt & DEGREES)) ? DEGREES : 0;
			else
				error(24, 1, NULL);
		}
		else
			error(24, 1, NULL);
	else
		get_param4(env, argc, argv, i);
}

void	get_param2(t_env *env, int argc, char **argv, int *i)
{
	if (!ft_strcmp(argv[*i], "-print_keys"))
		env->opt += (!(env->opt & PRINT_KEYS)) ? PRINT_KEYS : 0;
	else if (!ft_strcmp(argv[*i], "-debug"))
		env->opt += (!(env->opt & DEBUG_MODE)) ? DEBUG_MODE : 0;
	else if (!ft_strcmp(argv[*i], "-antialias"))
	{
		if (*i + 1 < argc)
			env->antialias_level = ft_atou(argv[++(*i)]);
		else
			error(20, 0, NULL);
	}
	else if (!ft_strcmp(argv[*i], "-device"))
		if (*i + 1 < argc)
		{
			if (!ft_strcmp(argv[++(*i)], "cpu"))
				env->cl.device_type = CL_DEVICE_TYPE_CPU;
			else if (!ft_strcmp(argv[*i], "gpu"))
				env->cl.device_type = CL_DEVICE_TYPE_GPU;
			else
				error(22, 0, NULL);
		}
		else
			error(21, 0, NULL);
	else
		get_param3(env, argc, argv, i);
}

void	get_param(t_env *env, int argc, char **argv, int *i)
{
	if (!ft_strcmp(argv[*i], "-title"))
		if (*i + 1 < argc)
		{
			free(env->win->name);
			env->win->name = ft_strdup(argv[++(*i)]);
			SDL_SetWindowTitle(env->win->win, env->win->name);
		}
		else
			error(18, 0, NULL);
	else if (!ft_strcmp(argv[*i], "-size"))
		if (*i + 2 < argc)
		{
			env->win->w = ft_atou(argv[++(*i)]);
			env->win->h = ft_atou(argv[++(*i)]);
			SDL_SetWindowSize(env->win->win, env->win->w, env->win->h);
			SDL_SetWindowPosition(env->win->win, SDL_WINDOWPOS_CENTERED,
					SDL_WINDOWPOS_CENTERED);
		}
		else
			error(19, 0, NULL);
	else
		get_param2(env, argc, argv, i);
}

void	get_flags(t_env *env, int argc, char **argv)
{
	int		i;

	i = 1;
	while (i < argc)
	{
		if (argv[i][0] == '-')
			get_param(env, argc, argv, &i);
		else if (!env->file)
			env->file = argv[i];
		else
			error(16, 0, argv[i]);
		i++;
	}
}
