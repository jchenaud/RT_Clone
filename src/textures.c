/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 07:45:52 by pribault          #+#    #+#             */
/*   Updated: 2017/09/15 07:39:22 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static t_img	*convert(t_img *img)
{
	t_color	color;
	t_img	*new;
	Uint8	format;
	size_t	i;

	format = img->format->BytesPerPixel;
	if (format == 4)
		return (img);
	new = new_img(img->w, img->h);
	i = 0;
	color = (t_color){0, 0, 0, 255};
	while (i < (size_t)(img->w * img->h))
	{
		ft_memcpy(&color, img->pixels + i * format, format);
		ft_memcpy(new->pixels + i * 4, &color, 4);
		i++;
	}
	SDL_FreeSurface(img);
	return (new);
}

static int		find_texture(t_vector *textures, char *file)
{
	t_texture	*texture;
	size_t		i;

	i = 0;
	if (!textures || !file)
		return (-1);
	while (i < textures->n)
	{
		texture = (t_texture*)ft_vector_get(textures, i);
		if (!ft_strcmp(texture->name, file))
			return (i);
		i++;
	}
	ft_vector_resize(textures, i + 1);
	texture = (t_texture*)ft_vector_get(textures, i);
	if (!(texture->img = IMG_Load(file)))
	{
		ft_vector_resize(textures, i);
		return (-1);
	}
	texture->img = convert(texture->img);
	texture->name = ft_strdup(file);
	return (i);
}

void			convert_for_graphic(t_cl *cl, t_vector *vector)
{
	t_img	*img;
	size_t	size;
	size_t	i;

	i = 0;
	cl->textures_size = 0;
	while (i < vector->n)
	{
		img = ((t_texture*)ft_vector_get(vector, i))->img;
		size = sizeof(t_img) + sizeof(t_color) * img->w * img->h;
		ft_realloc(&cl->textures, cl->textures_size, cl->textures_size + size);
		ft_memcpy(cl->textures + cl->textures_size, img, sizeof(t_img));
		ft_memcpy(cl->textures + cl->textures_size + sizeof(t_img),
		img->pixels, size - sizeof(t_img));
		cl->textures_size += size;
		SDL_FreeSurface(img);
		i++;
	}
	if (vector->n)
	{
		cl->textures_mem = create_buffer(cl, CL_MEM_COPY_HOST_PTR,
		cl->textures_size, cl->textures);
		free(cl->textures);
	}
	ft_vector_del(&vector);
}

void			allocate_textures(t_env *env)
{
	char	*tmp;
	size_t	i;
	size_t	j;

	i = 0;
	if (!(env->textures = ft_vector_new(sizeof(t_texture), 0)))
		error(1, 1, NULL);
	while (i < env->cl.n_obj)
	{
		j = 0;
		while (j < 3)
		{
			tmp = env->cl.obj[i].mat.textures[j].name;
			env->cl.obj[i].mat.textures[j].n = find_texture(env->textures,
			tmp);
			free(tmp);
			j++;
		}
		i++;
	}
	convert_for_graphic(&env->cl, env->textures);
}