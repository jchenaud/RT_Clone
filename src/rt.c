/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/20 16:42:31 by pribault          #+#    #+#             */
/*   Updated: 2017/08/21 11:21:10 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		main(int argc, char **argv)
{
	t_obj 		test;
	cl_float3	vec;

	bzero(&test, sizeof(t_obj));
	get_plan(test).norm.x = 42;
	printf("total=%u union=%u hitbox=%u\n", sizeof(t_obj), sizeof(t_union), sizeof(t_hitbox));
	argc++;
	argv++;
	return (0);
}
