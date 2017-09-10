#include "kernel/kernel.hcl"

#define get_vector_norm(a)	sqrt(a->x * a->x + a->y * a->y + a->z * a->z)
#define add_vectors(a, b)	(float3){a.x + b.x, a.y + b.y, a.z + b.z}

inline void	normalize_vector(float3 *vec)
{
	float	norm = get_vector_norm(vec);

	vec->x /= norm;
	vec->y /= norm;
	vec->z /= norm;
}

inline void	rotate_point(float *x, float *y, float angle)
{
	float	c = cos(angle);
	float	s = sin(angle);
	float	t_x;

	t_x = *x;
	*x = *x * c - *y * s;
	*y = t_x * s + *y * c;
}

inline void	rotate_vec(float3 *vec, float3 angle)
{
	rotate_point(&((t_vec3*)vec)->x, &((t_vec3*)vec)->y, angle.z);
	rotate_point(&((t_vec3*)vec)->x, &((t_vec3*)vec)->z, angle.y);
	rotate_point(&((t_vec3*)vec)->y, &((t_vec3*)vec)->z, angle.x);
}

__kernel void	cam_rays(__global t_cam *cam, __global t_ray *rays,
				__global size_t *m, __global size_t *max)
{
	t_ray		ray;
	int			id = get_global_id(0);
	float		l;

	ray.dir = (float3){1, 0, 0};
	l = 2 * cam->dis * tan(cam->fov.x / 2);
	ray.dir.y = (2 * l * (id % cam->w)) / (cam->w - 1) - l;
	l = 2 * cam->dis * tan(cam->fov.y / 2);
	ray.dir.z = (2 * l * ((id / cam->w) + *m * cam->h)) / (cam->h * *max - 1) - l;

	rotate_vec(&ray.dir, cam->rot);
	ray.pos = add_vectors(cam->pos, ray.dir);
	ray.f = 1;
	normalize_vector(&ray.dir);
	rays[id] = ray;
}
