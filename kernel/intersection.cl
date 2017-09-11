#include "kernel/kernel.hcl"

inline float	hit_sphere(__global t_ray *ray, __global t_obj *obj)
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

inline float	hit_plan(__global t_ray *ray, __global t_obj *obj)
{
	float	h;

	h = scalar_vectors(get_plan(obj).norm, ray->dir);
	if (h == 0)
		return (-42);
	return (-(scalar_vectors(get_plan(obj).norm, sub_vectors(ray->pos, obj->pos))) / h);
}

inline float	hit_cylinder(__global t_ray *ray, __global t_obj *obj)
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

inline float	hit_cone(__global t_ray *ray, __global t_obj *obj)
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

__kernel void	intersection(__global t_intersec *intersec, __global t_intersec *prev, __global t_ray *ray,
							__global uint *n_obj, __global t_obj *obj,
							__global uint *n_light, __global t_light *light)
{
	t_intersec	ret = {-1, -1};
	float		h;
	int			id = get_global_id(0);
	uint		i = 0;

	ray = &ray[id];
	prev = &prev[id / 2];
	if (ray->dir.x == 0 && ray->dir.y == 0 && ray->dir.z == 0)
	{
		intersec[id] = (t_intersec){-1, -1};
		return ;
	}
	while (i < *n_obj)
	{
		h = -1;
		if (prev->obj == -1 || (int)i != prev->obj)
		{
			if (obj[i].type == SPHERE)
				h = hit_sphere(ray, &obj[i]);
			else if (obj[i].type == PLAN)
				h = hit_plan(ray, &obj[i]);
			else if (obj[i].type == CYLINDER)
				h = hit_cylinder(ray, &obj[i]);
			else if (obj[i].type == CONE)
				h = hit_cone(ray, &obj[i]);
			if (h > 0.01 && (h < ret.h || ret.h == -1))
			{
				ret.obj = i;
				ret.h = h;
			}
		}
		i++;
	}
	intersec[id] = ret;
}
