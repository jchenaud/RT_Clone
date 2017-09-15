/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preview.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/11 02:50:57 by pribault          #+#    #+#             */
/*   Updated: 2017/09/13 00:47:28 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	launch_preview(t_cl *cl, t_cam *cam, t_color *img)
{
	cl_mem	img_mem;

	img_mem = create_buffer(cl, CL_MEM_ALLOC_HOST_PTR,
	sizeof(t_color) * cam->w * cam->h, NULL);
	set_kernel_arg(&cl->preview, &img_mem, 0);
	set_kernel_arg(&cl->preview, &cl->rays, 1);
	set_kernel_arg(&cl->preview, &cl->n_obj_mem, 2);
	set_kernel_arg(&cl->preview, &cl->obj_mem, 3);
	nd_range_kernel(cl, &cl->preview, cam->w * cam->h);
	read_buffer(cl, img_mem, img,
	sizeof(t_color) * cam->w * cam->h);
	delete_buffer(img_mem);
}

void		render_preview(t_env *env, t_cam *cam, t_img *img)
{
	SDL_Texture	*texture;
	t_cam		tmp;

	ft_memcpy(&tmp, cam, sizeof(t_cam));
	tmp.w = img->w;
	tmp.h = img->h;
	create_cam_rays(env, &tmp, 0, 1);
	launch_preview(&env->cl, &tmp, img->pixels);
	delete_buffer(env->cl.rays);
	texture = SDL_CreateTextureFromSurface(env->win->render, img);
	SDL_RenderCopy(env->win->render, texture, NULL, NULL);
	SDL_RenderPresent(env->win->render);
	SDL_DestroyTexture(texture);
	SDL_FreeSurface(img);
}