/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/22 18:42:46 by pribault          #+#    #+#             */
/*   Updated: 2017/08/22 18:44:55 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	key_pressed(int k, t_env *env)
{
	if (env->opt & PRINT_KEYS)
		ft_printf("key %d pressed\n", k);
	if (k == 53)
		exit(0);
}

void	key_released(int k, t_env *env)
{
	if (env->opt & PRINT_KEYS)
		ft_printf("key %d released\n", k);
}
