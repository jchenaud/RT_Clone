/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/31 06:00:45 by pribault          #+#    #+#             */
/*   Updated: 2017/08/31 06:05:11 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "librainbow.h"

inline t_color	new_color(t_uchar r, t_uchar g, t_uchar b, t_uchar a)
{
	return ((t_color){g, b, r, a});
}
