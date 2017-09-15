/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_del.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/01 00:57:28 by pribault          #+#    #+#             */
/*   Updated: 2017/09/01 01:04:25 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_vector_del(t_vector **vector)
{
	if (!vector || !*vector)
		return ;
	free((*vector)->ptr);
	free(*vector);
	*vector = NULL;
}
