/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_fps.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/28 02:31:50 by pribault          #+#    #+#             */
/*   Updated: 2017/08/29 04:34:01 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private.h"

t_uint	get_fps(void)
{
	static struct timeval	prev;
	struct timeval			now;
	static t_uint			fps = 0;
	static t_uint			mem = 0;

	mem++;
	if (mem != 2 && !(gettimeofday(&now, NULL)))
	{
		fps = 1000000 * (now.tv_sec - prev.tv_sec) +
		now.tv_usec - prev.tv_usec;
		fps = (fps) ? (mem * 1000000) / fps : -1;
		prev = now;
		mem = 0;
	}
	return (fps);
}
