/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/24 00:45:05 by pribault          #+#    #+#             */
/*   Updated: 2017/08/24 00:47:41 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libimages.h"

int		main(int argc, char **argv)
{
	t_img	*img;

	if (argc == 3)
	{
		img = import_bmp(argv[1]);
		if (img)
			export_bmp(img, argv[2]);
		else
			ft_printf("rip x_x\n");
	}
	else
		return (1);
	return (0);
}
