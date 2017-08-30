/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/27 16:59:21 by pribault          #+#    #+#             */
/*   Updated: 2017/08/27 17:02:31 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private.h"

char		*get_version(void)
{
	return ("1.0");
}

t_uint16	get_width(t_win *win)
{
	return (win->w);
}

t_uint16	get_height(t_win *win)
{
	return (win->h);
}

char		*get_title(t_win *win)
{
	return (win->name);
}
