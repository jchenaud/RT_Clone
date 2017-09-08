/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   antialiasing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/26 23:39:24 by pribault          #+#    #+#             */
/*   Updated: 2017/09/08 04:14:15 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		antialiase(t_uchar antialias, t_cl *cl, t_img *img)
{
	t_resize_buff	mem;
	size_t			n;
	size_t			i;

	n = img->w * img->h;
	i = 0;
	while (i++ < antialias)
	{
		mem.img_src = create_buffer(cl, CL_MEM_COPY_HOST_PTR,
		sizeof(t_img), img);
		mem.dest = create_buffer(cl, CL_MEM_ALLOC_HOST_PTR,
		sizeof(t_color) * img->w * img->h, NULL);
		mem.src = create_buffer(cl, CL_MEM_COPY_HOST_PTR,
		sizeof(t_color) * img->w * img->h, img->pixels);
		set_kernel_arg(&cl->antialiasing, &mem.img_src, 0);
		set_kernel_arg(&cl->antialiasing, &mem.dest, 1);
		set_kernel_arg(&cl->antialiasing, &mem.src, 2);
		nd_range_kernel(cl, &cl->antialiasing, n);
		read_buffer(cl, mem.dest, img->pixels, n * sizeof(t_color));
	}
}
