typedef struct	s_cam
{
	float3		pos;
	float3		rot;
	float3		dir;
	float2		fov;
	float		dis;
	uint		w;
	uint		h;
	void		*img;
	char		*output;
}				t_cam;

typedef struct	s_ray
{
	float3		pos;
	float3		dir;
	float		f;
}				t_ray;

typedef struct	s_vec3
{
	float		x;
	float		y;
	float		z;
}				t_vec3;

#define add_vectors(a, b)	(float3){a.x + b.x, a.y + b.y, a.z + b.z}

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

__kernel void	cam_rays(__global t_cam *cam, __global t_ray *rays)
{
	t_ray		ray;
	int			id = get_global_id(0);
	float		l;

	ray.dir = (float3){1, 0, 0};
	l = 2 * cam->dis * tan(cam->fov.x / 2);
	ray.dir.y = (2 * l * (id % cam->w)) / (cam->w - 1) - l;
	l = 2 * cam->dis * tan(cam->fov.y / 2);
	ray.dir.z = (2 * l * (id / cam->w)) / (cam->h - 1) - l;

	rotate_vec(&ray.dir, cam->rot);
	ray.pos = add_vectors(cam->pos, ray.dir);
	ray.f = 1;
	rays[id] = ray;
}