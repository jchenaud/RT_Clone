/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/22 18:46:43 by pribault          #+#    #+#             */
/*   Updated: 2017/09/29 17:24:39 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double		get_speed(void)
{
	static struct timeval	prev;
	static size_t			i = 10;
	static double			ret;
	struct timeval			t;

	if (i >= 10)
	{
		gettimeofday(&t, NULL);
		ret = ((t.tv_usec - prev.tv_usec) + (t.tv_sec - prev.tv_sec) * 1000000)
		/ (double)1000000;
		ret /= 10;
		prev = t;
		i = 0;
	}
	i++;
	return ((ret > 100) ? 0 : ret);
}

static void	create_buffers(t_cl *cl)
{
	cl->n_obj_mem = create_buffer(cl, CL_MEM_COPY_HOST_PTR,
	sizeof(t_uint), &cl->n_obj);
	cl->obj_mem = create_buffer(cl, CL_MEM_COPY_HOST_PTR,
	sizeof(t_obj) * cl->n_obj, cl->obj);
	cl->n_light_mem = create_buffer(cl, CL_MEM_COPY_HOST_PTR,
	sizeof(t_uint), &cl->n_light);
	cl->light_mem = create_buffer(cl, CL_MEM_COPY_HOST_PTR,
	sizeof(t_light) * cl->n_light, cl->light);
}

void		launch_kernel(t_env *env)
{
	struct timeval	start;
	struct timeval	end;
	double			diff;
	t_list			*cams;
	t_cam			*cam;

	if (!env->cl.n_obj || !env->cl.n_light)
		error((!env->cl.n_obj) ? 50 : 51, 1, NULL);
	cams = env->cam;
	create_buffers(&env->cl);
	while (cams)
	{
		ft_putchar('\n');
		cam = (t_cam*)cams->content;
		gettimeofday(&start, NULL);
		dispatch_rays(env, cam);
		gettimeofday(&end, NULL);
		diff = (end.tv_sec - start.tv_sec) +
		(end.tv_usec - start.tv_usec) / (double)1000000;
		printf("\033[1A\033[0K%s: took %.2luh %.2lumin %.2lus %.3lums\n",
		cam->output, ((size_t)diff) / 3600, (((size_t)diff) % 3600) / 60,
		((size_t)diff) % 60, (size_t)(diff * 1000) % 1000);
		antialiase(env->antialias_level, &env->cl, cam->img);
		cams = cams->next;
	}
}

t_list		*get_list_n(t_list *list, int n)
{
	int		i;

	i = 0;
	while (i < n && list)
	{
		i++;
		list = list->next;
	}
	return (list);
}

int			loop(t_env *env)
{
	if (env->opt & PREVIEW)
		render_preview(env, get_list_n(env->cam, env->n - env->i - 1)->content,
		env->preview);
	else
		render_texture(env->win->render, env->img[env->i]);
	while (1)
	{
		while (SDL_PollEvent(&env->win->events))
			keys(env, &env->win->events);
		ft_printf("\033[1A\033[Kw=%d h=%d\n", env->win->w, env->win->h);
	}
	return (0);
}
