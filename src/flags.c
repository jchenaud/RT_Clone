/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/22 17:18:56 by pribault          #+#    #+#             */
/*   Updated: 2017/08/23 12:21:41 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	get_param(t_env *env, int argc, char **argv, int *i)
{
	if (!ft_strcmp(argv[*i], "-title"))
	{
		if (*i + 1 < argc)
			env->win.name = argv[++(*i)];
		else
			error(18, 0, NULL);
	}
	else if (!ft_strcmp(argv[*i], "-size"))
	{
		if (*i + 2 < argc)
		{
			env->win.w = ft_atou(argv[++(*i)]);
			env->win.h = ft_atou(argv[++(*i)]);
		}
		else
			error(19, 0, NULL);
	}
	else if (!ft_strcmp(argv[*i], "-print_keys"))
		env->opt += (!env->opt & PRINT_KEYS) ? PRINT_KEYS : 0;
	else
		error(17, 0, argv[*i]);
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
