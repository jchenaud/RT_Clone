#include "kernel/kernel.hcl"

inline t_color	add_colors(t_color a, t_color b)
{
	return ((t_color){(a.g + b.g) % 256, (a.b + b.b) % 256, (a.r + b.r) % 256, 255});
}

inline t_color	mult_color(t_color a, float f)
{
	return ((t_color){(size_t)(a.g * f) % 256, (size_t)(a.b * f) % 256, (size_t)(a.r * f) % 256, 255});
}

inline void	normalize_vector(float3 *vec)
{
	float	norm = get_vector_norm(vec);

	vec->x /= norm;
	vec->y /= norm;
	vec->z /= norm;
}

inline float	hit_sphere(t_ray *ray, __global t_obj *obj)
{
	float3	x = sub_vectors(ray->pos, obj->pos);
	float	a = scalar_vectors(ray->dir, ray->dir);
	float	b = 2 * scalar_vectors(ray->dir, x);
	float	c = scalar_vectors(x, x) - get_sphere(obj).rad * get_sphere(obj).rad;
	float	delta = b * b - 4 * a * c;
	float	h1;
	float	h2;

	if (delta < 0)
		return (-1);
	h1 = (-b - sqrt(delta)) / (2 * a);
	h2 = (-b + sqrt(delta)) / (2 * a);
	if (h1 < 0)
		return (h2);
	if (h2 < 0)
		return (h1);
	return ((h1 < h2) ? h1 : h2);
}

inline float3	get_sphere_norm(__global t_obj *obj, float3 *point)
{
	float3	ret;

	ret = sub_vectors((*point), obj->pos);
	normalize_vector(&ret);
	return (ret);
}

inline float	hit_plan(t_ray *ray, __global t_obj *obj)
{
	float	h;

	h = scalar_vectors(get_plan(obj).norm, ray->dir);
	if (h == 0)
		return (-42);
	return (-(scalar_vectors(get_plan(obj).norm, sub_vectors(ray->pos, obj->pos))) / h);
}

inline float	hit_cylinder(t_ray *ray, __global t_obj *obj)
{
	float3		x = sub_vectors(ray->pos, obj->pos);
	float		a = scalar_vectors(ray->dir, ray->dir) - pown(scalar_vectors(ray->dir, get_cylinder(obj).norm), 2);
	float		b = 2 * (scalar_vectors(ray->dir, x) - scalar_vectors(ray->dir, get_cylinder(obj).norm) * scalar_vectors(x, get_cylinder(obj).norm));
	float		c = scalar_vectors(x, x) - pown(scalar_vectors(x, get_cylinder(obj).norm), 2) - get_cylinder(obj).rad * get_cylinder(obj).rad;
	float		delta = b * b - 4 * a * c;
	float		h1;
	float		h2;

	if (delta < 0)
		return (-1);
	h1 = (-b - sqrt(delta)) / (2 * a);
	h2 = (-b + sqrt(delta)) / (2 * a);
	if (h1 < 0)
		return (h2);
	if (h2 < 0)
		return (h1);
	return ((h1 < h2) ? h1 : h2);
}

inline float3	get_cylinder_norm(__global t_obj *obj, float3 *point)
{
	float3	norm;
	float3	tmp1;
	float	tmp;

	tmp1 = sub_vectors((*point), obj->pos);
	tmp = scalar_vectors(tmp1, get_cylinder(obj).norm);
	norm = sub_vectors(tmp1, new_vector(tmp * get_cylinder(obj).norm.x, tmp * get_cylinder(obj).norm.y, tmp * get_cylinder(obj).norm.z));
	return (norm);
}

inline float	hit_cone(t_ray *ray, __global t_obj *obj)
{
	float3		x = sub_vectors(ray->pos, obj->pos);
	float		t = scalar_vectors(ray->dir, get_cone(obj).norm);
	float		k = 1 + pow(tan(get_cone(obj).angle), 2);
	float		a = scalar_vectors(ray->dir, ray->dir) - k * t * t;
	float		b = 2 * (scalar_vectors(ray->dir, x) - k * t * scalar_vectors(x, get_cone(obj).norm));
	float		c = scalar_vectors(x, x) - k * pow(scalar_vectors(x, get_cone(obj).norm), 2);
	float		delta = b * b - 4 * a * c;
	float		h1;
	float		h2;

	if (delta < 0)
		return (-1);
	h1 = (-b - sqrt(delta)) / (2 * a);
	h2 = (-b + sqrt(delta)) / (2 * a);
	if (h1 < 0)
		return (h2);
	if (h2 < 0)
		return (h1);
	return ((h1 < h2) ? h1 : h2);
}

inline float3	get_cone_norm(__global t_obj *obj, float3 *point)
{
	float3	norm;
	float3	tmp1;
	float	tmp;

	tmp1 = sub_vectors((*point), obj->pos);
	tmp = scalar_vectors(tmp1, get_cylinder(obj).norm);
	norm = sub_vectors(tmp1, new_vector(tmp * get_cylinder(obj).norm.x, tmp * get_cylinder(obj).norm.y, tmp * get_cylinder(obj).norm.z));
	return (norm);
}

__kernel void	render_img(__global t_color *img, __global size_t *p,
				__global t_ray *ray, __global t_intersec *intersec,
				__global uint *n_obj, __global t_obj *obj,
				__global uint *n_light, __global t_light *light,
				__global size_t *j)
{
	t_color	color = (t_color){0, 0, 0, 255};
	t_ray	vec;
	float3	norm;
	float3	fact = (float3){0, 0, 0};
	float	alpha;
	float	h_tmp;
	float	tmp;
	float	h;
	int		id = *p * get_global_id(0) + *j;
	uint	i = 0;
	uint	k;

	img = &img[id / *p];
	intersec = &intersec[id];
	ray = &ray[id];
	if ((ray->dir.x == 0 && ray->dir.y == 0 && ray->dir.z == 0) ||
	intersec->h <= 0.01 || intersec->obj == -1 || ray->f == 0)
	{
		*img = add_colors(*img, (t_color){0, 0, 0, 255});
		return ;
	}
	vec.pos = (float3){intersec->h * ray->dir.x + ray->pos.x, intersec->h * ray->dir.y + ray->pos.y, intersec->h * ray->dir.z + ray->pos.z};
#ifdef SWITCH
	switch (obj[intersec->obj].type)
	{
		case SPHERE:
			norm = get_sphere_norm(&obj[intersec->obj], &vec.pos);
		break;
		case PLAN:
			norm = get_plan((&obj[intersec->obj])).norm;
		break;
		case CYLINDER:
			norm = get_cylinder_norm(&obj[intersec->obj], &vec.pos);
		break;
		case CONE:
			norm = get_cone_norm(&obj[intersec->obj], &vec.pos);
		break;
	}
#else
	if (obj[intersec->obj].type == SPHERE)
		norm = get_sphere_norm(&obj[intersec->obj], &vec.pos);
	else if (obj[intersec->obj].type == PLAN)
		norm = get_plan((&obj[intersec->obj])).norm;
	else if (obj[intersec->obj].type == CYLINDER)
		norm = get_cylinder_norm(&obj[intersec->obj], &vec.pos);
	else if (obj[intersec->obj].type == CONE)
		norm = get_cone_norm(&obj[intersec->obj], &vec.pos);
	else
		norm = get_sphere_norm(&obj[intersec->obj], &vec.pos);
#endif
	normalize_vector(&norm);
	while (i < *n_light)
	{
		vec.dir = sub_vectors(light[i].pos, vec.pos);
		normalize_vector(&vec.dir);
		h_tmp = (light[i].pos.x - vec.pos.x) / vec.dir.x;
		tmp = 0;
		k = 0;
		alpha = 1;
		while (k < *n_obj)
		{
#ifdef SWITCH
			switch (obj[k].type)
			{
				case SPHERE:
					if ((h = hit_sphere(&vec, &obj[k])) > 0.01 && h < h_tmp)
					{
						if (obj[k].mat.col.a != 255)
							alpha *= ((255 - obj[k].mat.col.a) / (float)255);
						else
							k = *n_obj;
					}
				break;
				case PLAN:
					if ((h = hit_plan(&vec, &obj[k])) > 0.01 && h < h_tmp)
					{
						if (obj[k].mat.col.a != 255)
							alpha *= ((255 - obj[k].mat.col.a) / (float)255);
						else
							k = *n_obj;
					}
				break;
				case CYLINDER:
					if ((h = hit_cylinder(&vec, &obj[k])) > 0.01 && h < h_tmp)
					{
						if (obj[k].mat.col.a != 255)
							alpha *= ((255 - obj[k].mat.col.a) / (float)255);
						else
							k = *n_obj;
					}
				break;
				case CONE:
					if ((h = hit_cone(&vec, &obj[k])) > 0.01 && h < h_tmp)
					{
						if (obj[k].mat.col.a != 255)
							alpha *= ((255 - obj[k].mat.col.a) / (float)255);
						else
							k = *n_obj;
					}
				break;
			}
#else
			if (obj[k].type == SPHERE)
			{
				if ((h = hit_sphere(&vec, &obj[k])) > 0.01 && h < h_tmp)
				{
					if (obj[k].mat.col.a != 255)
						alpha *= ((255 - obj[k].mat.col.a) / (float)255);
					else
						k = *n_obj;
				}
			}
			else if (obj[k].type == PLAN)
			{
				if ((h = hit_plan(&vec, &obj[k])) > 0.01 && h < h_tmp)
				{
					if (obj[k].mat.col.a != 255)
						alpha *= ((255 - obj[k].mat.col.a) / (float)255);
					else
						k = *n_obj;
				}
			}
			else if (obj[k].type == CONE)
			{
				if ((h = hit_cone(&vec, &obj[k])) > 0.01 && h < h_tmp)
				{
					if (obj[k].mat.col.a != 255)
						alpha *= ((255 - obj[k].mat.col.a) / (float)255);
					else
						k = *n_obj;
				}
			}
			else if (obj[k].type == CYLINDER)
			{
				if ((h = hit_cylinder(&vec, &obj[k])) > 0.01 && h < h_tmp)
				{
					if (obj[k].mat.col.a != 255)
						alpha *= ((255 - obj[k].mat.col.a) / (float)255);
					else
						k = *n_obj;
				}
			}
#endif
			k++;
		}
		tmp = (light[i].i.x * obj[intersec->obj].mat.ref.x);
		if (k == *n_obj)
		{
			tmp += (light[i].i.y * obj[intersec->obj].mat.ref.y * ((scalar_vectors(vec.dir, norm) >= 0) ? scalar_vectors(vec.dir, norm) : 0));
			vec.dir = sub_vectors(vec.dir, mult_vector(mult_vector(norm, scalar_vectors(vec.dir, norm)), 2));
			normalize_vector(&vec.dir);
			fact = add_vectors(fact, mult_vector(new_vector(1, 1, 1), (light[i].i.z * obj[intersec->obj].mat.ref.z * pow(scalar_vectors(mult_vector(ray->dir, 0.99), vec.dir), ALPHA))));
		}
		tmp *= alpha;
		fact.x += (tmp * light[i].col.r) / (float)255;
		fact.y += (tmp * light[i].col.g) / (float)255;
		fact.z += (tmp * light[i].col.b) / (float)255;
		i++;
	}
	color = mult_color(obj[intersec->obj].mat.col, (1 - obj[intersec->obj].mat.ref.w) * (obj[intersec->obj].mat.col.a / (float)255));
	// if (color.r * fact.x < 256)
	// {
	// 	if (color.r * fact.x >= 0)
	// 		color.r *= fact.x;
	// 	else
	// 		color.r = 0;
	// }
	// else
	// 	color.r = 255;
	// if (color.g * fact.y < 256)
	// {
	// 	if (color.g * fact.y >= 0)
	// 		color.g *= fact.y;
	// 	else
	// 		color.g = 0;
	// }
	// else
	// 	color.g = 255;
	// if (color.b * fact.z < 256)
	// {
	// 	if (color.b * fact.z >= 0)
	// 		color.b *= fact.z;
	// 	else
	// 		color.b = 0;
	// }
	// else
	// 	color.b = 255;
	color.r = (size_t)(color.r * fact.x) % 256;
	color.g = (size_t)(color.g * fact.y) % 256;
	color.b = (size_t)(color.b * fact.z) % 256;
	color.a = 255;
	*img = add_colors(*img, mult_color(color, ray->f));
}
