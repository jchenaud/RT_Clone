/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_window.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/27 16:54:11 by pribault          #+#    #+#             */
/*   Updated: 2017/08/27 16:58:45 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private.h"

void	delete_window(t_win **win)
{
	if (!win || !(*win))
		return ;
	free((*win)->name);
	free(*win);
	*win = NULL;
}
