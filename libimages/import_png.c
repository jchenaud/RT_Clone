/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   import_png.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/24 01:18:12 by pribault          #+#    #+#             */
/*   Updated: 2017/08/24 01:19:11 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libimages.h"

int		main(int argc, char **argv)
{
	t_img	*img;

	if (argc == 2)
	{
		img = import_png(argv[1]);
	}
	else
		return (1);
	return (0);
}
