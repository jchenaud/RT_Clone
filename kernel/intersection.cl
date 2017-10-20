#include "kernel/kernel.hcl"

/*
**	rotate x and y in 2d
*/

inline void	rotate_point(float *x, float *y, float angle)
{
	float	c = cos(angle);
	float	s = sin(angle);
	float	t_x;

	t_x = *x;
	*x = *x * c - *y * s;
	*y = t_x * s + *y * c;
}

/*
**	rotate in 3d by multiple rotations in 2d
*/

inline void	rotate_vec(float3 *vec, float3 angle)
{
	rotate_point(&((t_vec3*)vec)->x, &((t_vec3*)vec)->y, angle.z);
	rotate_point(&((t_vec3*)vec)->x, &((t_vec3*)vec)->z, angle.y);
	rotate_point(&((t_vec3*)vec)->y, &((t_vec3*)vec)->z, angle.x);
}

/*
**	check if a ray hit an object in it's hitbox
**	this function allow hitbox rotation around the object center
*/

inline char		check_hitbox(__global t_hitbox *hitbox, __global float3 *center, __global t_ray *ray, float *h)
{
	float3	point = (float3){ray->dir.x * *h + ray->pos.x, ray->dir.y * *h + ray->pos.y, ray->dir.z * *h + ray->pos.z};

	point = sub_vectors(point, (*center));
	rotate_vec(&point, (float3){-hitbox->rot.x, -hitbox->rot.y, -hitbox->rot.z});
	point = add_vectors(point, (*center));
	if (point.x < hitbox->min.x || point.x > hitbox->max.x ||
		point.y < hitbox->min.y || point.y > hitbox->max.y ||
		point.z < hitbox->min.z || point.z > hitbox->max.z)
		return ((hitbox->type & INVISIBLE) ? 1 : 0);
	return ((hitbox->type & INVISIBLE) ? 0 : 1);
}

/*
**	check if a ray hit a given sphere
*/

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
	h1 = (check_hitbox(&obj->hitbox, &obj->pos, ray, &h1)) ? h1 : -1;
	h2 = (check_hitbox(&obj->hitbox, &obj->pos, ray, &h2)) ? h2 : -1;
	if (h1 < MARGE)
		return (h2);
	if (h2 < MARGE)
		return (h1);
	return ((h1 < h2) ? h1 : h2);
}

/*
**	check if a ray hit a given plan
*/

inline float	hit_plan(__global t_ray *ray, __global t_obj *obj)
{
	float	h;

	h = scalar_vectors(get_plan(obj).norm, ray->dir);
	if (h == 0)
		return (-42);
	h = -(scalar_vectors(get_plan(obj).norm, sub_vectors(ray->pos, obj->pos))) / h;
	h = (check_hitbox(&obj->hitbox, &obj->pos, ray, &h)) ? h : -1;
	return (h);
}

/*
**	check if a ray hit a given cylinder
*/

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
	h1 = (check_hitbox(&obj->hitbox, &obj->pos, ray, &h1)) ? h1 : -1;
	h2 = (check_hitbox(&obj->hitbox, &obj->pos, ray, &h2)) ? h2 : -1;
	if (h1 < MARGE)
		return (h2);
	if (h2 < MARGE)
		return (h1);
	return ((h1 < h2) ? h1 : h2);
}

/*
**	check if a ray hit a given cone
*/

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
	h1 = (check_hitbox(&obj->hitbox, &obj->pos, ray, &h1)) ? h1 : -1;
	h2 = (check_hitbox(&obj->hitbox, &obj->pos, ray, &h2)) ? h2 : -1;
	if (h1 < 0)
		return (h2);
	if (h2 < 0)
		return (h1);
	return ((h1 < h2) ? h1 : h2);
}

/*
**	find for each ray the nearest intersection with an object and write it in a buffer
*/

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
		if (obj[i].type == SPHERE)
			h = hit_sphere(ray, &obj[i]);
		else if (obj[i].type == PLAN)
			h = hit_plan(ray, &obj[i]);
		else if (obj[i].type == CYLINDER)
			h = hit_cylinder(ray, &obj[i]);
		else if (obj[i].type == CONE)
			h = hit_cone(ray, &obj[i]);
		else
			h = -1;
		if (h > MARGE && (h < ret.h || ret.h == -1))
		{
			ret.obj = i;
			ret.h = h;
		}
		i++;
	}
	intersec[id] = ret;
}
