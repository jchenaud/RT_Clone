/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/20 16:42:31 by pribault          #+#    #+#             */
/*   Updated: 2017/08/23 14:49:26 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_env	*init_env(void)
{
	t_env	*env;

	if (!(env = (t_env*)malloc(sizeof(t_env))))
		error(1, 1, NULL);
	ft_bzero(env, sizeof(t_env));
	env->win.name = "RT";
	env->win.w = 1920;
	env->win.h = 1080;
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

void	alloc_images(t_win *win, t_list *cam)
{
	t_cam	*current;

	while (cam)
	{
		current = (t_cam*)cam->content;
		printf("cam %u\n", current->w);
		current->img = new_img(win, current->w, current->h);
		cam = cam->next;
	}
}

int		main(int argc, char **argv)
{
	t_env	*env;

	if (argc == 1)
		error(0, 1, NULL);
	env = init_env();
	get_flags(env, argc, argv);
	create_window(env, &env->win);
	init_opencl(&env->cl);
	if (parsing(env->file, env) == -1)
		error(64, 1, NULL);
	ft_printf("\n");
	env->cl.obj = alloc_array(env->obj, &env->cl.n_obj);
	env->cl.light = alloc_array(env->light, &env->cl.n_light);
	alloc_images(&env->win, env->cam);
	mlx_loop(env->win.mlx);
	return (0);
}
