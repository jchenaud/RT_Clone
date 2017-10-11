/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_iter.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/29 11:34:21 by pribault          #+#    #+#             */
/*   Updated: 2017/09/29 11:36:58 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_vector_iter(t_vector *vector, void (*f)(void*))
{
	size_t	i;

	if (!vector)
		return ;
	i = 0;
	while (i < vector->n)
		f(ft_vector_get(vector, i++));
}
