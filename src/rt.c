/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/20 16:42:31 by pribault          #+#    #+#             */
/*   Updated: 2017/10/20 15:21:30 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
**	initializing env struct
*/

t_env	*init_env(void)
{
	t_env	*env;

	if (!(env = (t_env*)malloc(sizeof(t_env))))
		error(1, 1, NULL);
	ft_bzero(env, sizeof(t_env));
	env->antialias_level = 2;
	env->iterations = 3;
	env->cl.device_type = CL_DEVICE_TYPE_GPU;
	env->i = 0;
	env->win = new_window("RT", 1280, 720);
	env->icone = IMG_Load("rt.png");
	env->preview = new_img(1280, 720);
	env->step = 1;
	env->rot_angle = PI / 32;
	return (env);
}

/*
**	transforming object or light list into an array to send it to the gpu later
*/

void	*alloc_array(t_list *head, t_uint *n)
{
	t_list	*list;
	size_t	size;
	char	*new;
	t_uint	i;

	*n = 0;
	list = head;
	while (list)
	{
		size = list->content_size;
		list = list->next;
		(*n)++;
	}
	if (!(new = (char*)malloc(size * (*n))))
		error(1, 1, NULL);
	i = 0;
	while (head)
	{
		ft_memcpy(&new[size * i++], head->content, size);
		head = head->next;
	}
	return ((void*)new);
}

/*
**	add prefabs in object array
*/

void	add_prefabs(t_env *env)
{
	t_prefab	*prefab;
	void		*new;
	t_uint		n;
	t_uint		i;

	n = 0;
	prefab = env->pf_o;
	while (prefab)
	{
		new = alloc_array(prefab->p_obj, &i);
		ft_realloc((void**)&env->cl.obj, sizeof(t_obj) * env->cl.n_obj,
		sizeof(t_obj) * (env->cl.n_obj + i));
		ft_memcpy(&env->cl.obj[env->cl.n_obj],
		new, sizeof(t_obj) * i);
		env->cl.n_obj += i;
		free(new);
		n++;
		prefab = prefab->next;
	}
}

/*
**	export images in files, convert them into textures
**	and place them in cam list.
**
**	you can notice that images are inverted,
**	sdl don't know how to export in the right sens
**	.____________________________________________.
*/

void	place_in_list(t_env *env)
{
	t_list	*cam;
	t_uint	n;
	t_uint	i;

	n = 0;
	cam = env->cam;
	while (cam)
	{
		n++;
		cam = cam->next;
	}
	env->n = n;
	if (!(env->img = (SDL_Texture**)malloc(sizeof(SDL_Texture*) * n)))
		error(1, 1, NULL);
	i = n - 1;
	cam = env->cam;
	while (cam)
	{
		invert_image(((t_cam*)cam->content)->img);
		IMG_SavePNG(((t_cam*)cam->content)->img,
		((t_cam*)cam->content)->output);
		env->img[i--] = SDL_CreateTextureFromSurface(env->win->render,
		((t_cam*)cam->content)->img);
		cam = cam->next;
	}
}

/*
**	do i really need to explain a main ? REALLY KEVIN ?!? 😡
*/

int		main(int argc, char **argv)
{
	t_env	*env;

	if (argc == 1)
		error(0, 1, NULL);
	env = init_env();
	SDL_SetWindowIcon(env->win->win, env->icone);
	get_flags(env, argc, argv);
	init_opencl(&env->cl);
	if (parsing(env->file, env) == -1)
		error(64, 1, NULL);
	env->cl.obj = alloc_array(env->obj, &env->cl.n_obj);
	env->cl.light = alloc_array(env->light, &env->cl.n_light);
	add_prefabs(env);
	if (env->opt & DEGREES)
		convert_to_radians(env->cl.obj, env->cl.n_obj);
	convert_rotations_to_normals(env->cl.obj, env->cl.n_obj);
	allocate_textures(env);
	alloc_images(env->cam);
	launch_kernel(env);
	place_in_list(env);
	loop(env);
	return (0);
}
