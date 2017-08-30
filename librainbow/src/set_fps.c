/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_fps.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/28 02:49:49 by pribault          #+#    #+#             */
/*   Updated: 2017/08/29 04:33:39 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private.h"

void	set_fps(t_uint fps)
{
	static struct timeval	prev;
	struct timeval			now;
	t_uint					diff;

	if (!(gettimeofday(&now, NULL)))
	{
		diff = 1000000 * (now.tv_sec - prev.tv_sec) +
		now.tv_usec - prev.tv_usec;
		prev = now;
		if (diff < 1000000 / fps)
			usleep(1000000 / fps - diff);
	}
}
