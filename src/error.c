/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/22 17:18:47 by pribault          #+#    #+#             */
/*   Updated: 2017/08/22 18:09:33 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	print_usage(void)
{
	ft_putstr("./rt <flags> <file>\n");
	ft_putstr("  -title <title>\n");
	ft_putstr("  -size <width> <height>");
}

void	error(int error, char state, void *param)
{
	ft_putstr("\033[38;5;160merror: ");
	if (error == 0)
		print_usage();
	else if (error == 1)
		ft_putstr("cannot allocate memory");
	else if (error == 2)
		ft_printf("cannot open %s", param);
	else if (error == 16)
		ft_printf("please, specify only one file <3 #%s", param);
	else if (error == 17)
		ft_printf("unknow parameter %s", param);
	else if (error == 18)
		ft_putstr("title need 1 argument");
	else if (error == 19)
		ft_putstr("size need 2 arguments");
	else
		ft_putstr("unknown error");
	ft_putstr("\033[0m\n");
	if (state)
		exit(1);
}
