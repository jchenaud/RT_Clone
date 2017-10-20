/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preview.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/11 02:50:57 by pribault          #+#    #+#             */
/*   Updated: 2017/10/20 15:15:06 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
**	render an image in preview mod
*/

static void	launch_preview(t_cl *cl, t_cam *cam, t_color *img)
{
	static t_cam	mem = (t_cam){{{0}}, {{0}}, {{0}}, {{0}}, 0, 0, 0, 0, 0};
	static cl_mem	cam_mem = NULL;
	static cl_mem	img_mem = NULL;

	cam_mem = create_buffer(cl, CL_MEM_COPY_HOST_PTR, sizeof(t_cam), cam);
	if (ft_memcmp(&cam->w, &mem.w, sizeof(cl_uint) * 2))
	{
		if (img_mem)
			delete_buffer(img_mem);
		img_mem = create_buffer(cl, CL_MEM_ALLOC_HOST_PTR,
		sizeof(t_color) * cam->w * cam->h, NULL);
		set_kernel_arg(&cl->preview, &img_mem, 0);
	}
	set_kernel_arg(&cl->preview, &cam_mem, 1);
	set_kernel_arg(&cl->preview, &cl->n_obj_mem, 2);
	set_kernel_arg(&cl->preview, &cl->obj_mem, 3);
	nd_range_kernel(cl, &cl->preview, cam->w * cam->h);
	read_buffer(cl, img_mem, img,
	sizeof(t_color) * cam->w * cam->h);
	delete_buffer(cam_mem);
	ft_memcpy(&mem, cam, sizeof(t_cam));
}

/*
**	render and print the preview
*/

void		render_preview(t_env *env, t_cam *cam, t_img *img)
{
	SDL_Texture	*texture;
	t_cam		tmp;

	ft_memcpy(&tmp, cam, sizeof(t_cam));
	tmp.w = img->w;
	tmp.h = img->h;
	tmp.img = img;
	launch_preview(&env->cl, &tmp, img->pixels);
	invert_image(img);
	texture = SDL_CreateTextureFromSurface(env->win->render, img);
	SDL_RenderCopy(env->win->render, texture, NULL, NULL);
	SDL_RenderPresent(env->win->render);
	SDL_DestroyTexture(texture);
}
