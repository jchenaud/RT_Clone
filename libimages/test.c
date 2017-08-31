/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/23 23:13:49 by pribault          #+#    #+#             */
/*   Updated: 2017/08/23 23:32:02 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libimages.h"

int		main(int argc, char **argv)
{
	t_color	color;
	t_img	*img;
	int		i;
	int		j;

	if (argc == 3)
	{
		export_bmp(import_png(argv[1]), argv[2]);
	}
	else
		return (1);
	return (0);
}
