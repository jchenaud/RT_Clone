/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/01 01:06:12 by pribault          #+#    #+#             */
/*   Updated: 2017/09/14 00:28:32 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#ifdef ENABLE_REALLOC

void	ft_realloc(void **ptr, size_t prev_size, size_t new_size)
{
	if (!ptr)
		return ;
	*ptr = realloc(*ptr, new_size);
	(void)prev_size;
}

#else

void	ft_realloc(void **ptr, size_t prev_size, size_t new_size)
{
	void	*new;

	if (!ptr || !(new = malloc(new_size)))
		return ;
	if (*ptr)
	{
		ft_memcpy(new, *ptr, prev_size);
		free(*ptr);
	}
	*ptr = new;
}

#endif
