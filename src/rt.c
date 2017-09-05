/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/20 16:42:31 by pribault          #+#    #+#             */
/*   Updated: 2017/09/05 09:53:56 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_env	*init_env(void)
{
	t_env	*env;

	if (!(env = (t_env*)malloc(sizeof(t_env))))
		error(1, 1, NULL);
	ft_bzero(env, sizeof(t_env));
	env->antialias_level = 2;
	return (env);
}

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

void	alloc_images(t_list *cam)
{
	t_cam	*current;

	while (cam)
	{
		current = (t_cam*)cam->content;
		current->img = new_img(current->w, current->h);
		cam = cam->next;
	}
}

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
	if (!(env->img = (t_img*)malloc(sizeof(t_img) * n)))
		error(1, 1, NULL);
	i = n - 1;
	cam = env->cam;
	while (cam)
	{
		invert_image(((t_cam*)cam->content)->img);
		IMG_SavePNG(((t_cam*)cam->content)->img,
		((t_cam*)cam->content)->output);
		ft_memcpy(&env->img[i--], ((t_cam*)cam->content)->img,
		sizeof(t_img));
		cam = cam->next;
	}
}

int		main(int argc, char **argv)
{
	t_env	*env;

	if (argc == 1)
		error(0, 1, NULL);
	env = init_env();
	env->win = new_window("RT", 1280, 720);
	get_flags(env, argc, argv);
	init_opencl(&env->cl);
	if (parsing(env->file, env) == -1)
		error(64, 1, NULL);
	// ft_printf("\n");
	env->cl.obj = alloc_array(env->obj, &env->cl.n_obj);
	env->cl.light = alloc_array(env->light, &env->cl.n_light);
	alloc_images(env->cam);
	launch_kernel(env);
	place_in_list(env);
	env->i = 0;
	loop(env);
	return (0);
}
