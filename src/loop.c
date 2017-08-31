/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/22 18:46:43 by pribault          #+#    #+#             */
/*   Updated: 2017/08/31 04:28:10 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	create_buffers(t_cl *cl)
{
	cl->n_obj_mem = clCreateBuffer(cl->context, CL_MEM_COPY_HOST_PTR,
	sizeof(t_uint), &cl->n_obj, &cl->error);
	if (cl->error != CL_SUCCESS)
		error(48, 1, &cl->error);
	cl->obj_mem = clCreateBuffer(cl->context, CL_MEM_COPY_HOST_PTR,
	cl->n_obj * sizeof(t_obj), cl->obj, &cl->error);
	if (cl->error != CL_SUCCESS)
		error(48, 1, &cl->error);
	cl->n_light_mem = clCreateBuffer(cl->context, CL_MEM_COPY_HOST_PTR,
	sizeof(t_uint), &cl->n_light, &cl->error);
	if (cl->error != CL_SUCCESS)
		error(48, 1, &cl->error);
	cl->light_mem = clCreateBuffer(cl->context, CL_MEM_COPY_HOST_PTR,
	cl->n_light * sizeof(t_light), cl->light, &cl->error);
	if (cl->error != CL_SUCCESS)
		error(48, 1, &cl->error);
}

void		set_kernel_args(t_cl *cl)
{
	if ((cl->error = clSetKernelArg(cl->raytracer, 2, sizeof(cl_mem),
	&cl->n_obj_mem)) != CL_SUCCESS)
		error(49, 1, &cl->error);
	if ((cl->error = clSetKernelArg(cl->raytracer, 3, sizeof(cl_mem),
	&cl->obj_mem)) != CL_SUCCESS)
		error(49, 1, &cl->error);
	if ((cl->error = clSetKernelArg(cl->raytracer, 4, sizeof(cl_mem),
	&cl->n_light_mem)) != CL_SUCCESS)
		error(49, 1, &cl->error);
	if ((cl->error = clSetKernelArg(cl->raytracer, 5, sizeof(cl_mem),
	&cl->light_mem)) != CL_SUCCESS)
		error(49, 1, &cl->error);
}

void		allocate_camera(t_cl *cl, t_cam *cam)
{
	cl->img_mem = clCreateBuffer(cl->context, CL_MEM_COPY_HOST_PTR,
	cam->img->w * cam->img->h * sizeof(t_color), cam->img->pixels, &cl->error);
	if (cl->error != CL_SUCCESS)
		error(48, 1, &cl->error);
	if ((cl->error = clSetKernelArg(cl->raytracer, 0, sizeof(cl_mem),
	&cl->img_mem)) != CL_SUCCESS)
		error(49, 1, &cl->error);
	cl->cam_mem = clCreateBuffer(cl->context, CL_MEM_COPY_HOST_PTR,
	sizeof(t_cam), cam, &cl->error);
	if (cl->error != CL_SUCCESS)
		error(48, 1, &cl->error);
	if ((cl->error = clSetKernelArg(cl->raytracer, 1, sizeof(cl_mem),
	&cl->cam_mem)) != CL_SUCCESS)
		error(49, 1, &cl->error);
}

void		launch_kernel(t_env *env)
{
	t_list	*cam;
	size_t	n;

	if (!env->cl.n_obj || !env->cl.n_light)
		error((!env->cl.n_obj) ? 50 : 51, 1, NULL);
	create_buffers(&env->cl);
	set_kernel_args(&env->cl);
	cam = env->cam;
	while (cam)
	{
		allocate_camera(&env->cl, (t_cam*)cam->content);
		n = ((t_cam*)cam->content)->w * ((t_cam*)cam->content)->h;
		clEnqueueNDRangeKernel(env->cl.queue, env->cl.raytracer, 1, NULL, &n,
		NULL, 0, NULL, NULL);
		if (clFinish(env->cl.queue) != CL_SUCCESS)
			error(52, 1, NULL);
		clEnqueueReadBuffer(env->cl.queue, env->cl.img_mem, CL_TRUE, 0,
		n * sizeof(t_color), ((t_cam*)cam->content)->img->pixels, 0, NULL,
		NULL);
		if (clFinish(env->cl.queue) != CL_SUCCESS)
			error(52, 1, NULL);
		antialiase(env->antialias_level, &env->cl, ((t_cam*)cam->content)->img);
		export_bmp(((t_cam*)cam->content)->img, "test.bmp");
		cam = cam->next;
	}
}

int			loop(t_env *env)
{
	SDL_Texture	*texture;

	while (1)
	{
		while (SDL_PollEvent(&env->win->events))
			keys(env, &env->win->events);
		if (env->i < env->n)
		{
			texture = SDL_CreateTextureFromSurface(env->win->render,
			&env->img[env->i]);
			SDL_RenderCopy(env->win->render, texture, NULL, NULL);
			SDL_DestroyTexture(texture);
		}
		SDL_RenderPresent(env->win->render);
	}
	return (0);
}
