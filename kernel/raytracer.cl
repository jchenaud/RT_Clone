typedef struct	s_color
{
	uchar		g;
	uchar		b;
	uchar		r;
	uchar		a;
}				t_color;

typedef struct	s_img
{
	void		*ptr;
	t_color		*img;
	int			w;
	int			h;
}				t_img;

typedef struct	s_hitbox
{
	uchar		type;
	float3		rot;
	float3		min;
	float3		max;
	float3		r_min;
	float3		r_max;
}				t_hitbox;

typedef struct	s_sphere
{
	float		rad;
}				t_sphere;

typedef struct	s_pave
{
	float3		size;
}				t_pave;

typedef struct	s_plan
{
	float3		norm;
}				t_plan;

typedef struct	s_cone
{
	float3		norm;
	float		angle;
}				t_cone;

typedef struct	s_cylinder
{
	float3		norm;
	float		rad;
}				t_cylinder;

typedef union	u_union
{
	t_pave		pave;
	t_sphere	sphere;
	t_plan		plan;
	t_cone		cone;
	t_cylinder	cylinder;
}				t_union;

typedef struct	s_mat
{
	t_color		col;
	cl_float4	ref;
	cl_float	refraction;
	t_texture	*textures[3];
}				t_mat;

typedef struct	s_obj
{
	float3		pos;
	float3		rot;
	uchar		type;
	t_mat		mat;
	t_hitbox	hitbox;
	t_union		obj;
}				t_obj;

typedef struct	s_light
{
	float3		pos;
	t_color		col;
	float3		i;
}				t_light;

typedef struct	s_cam
{
	float3		pos;
	float3		rot;
	float3		dir;
	float2		fov;
	float		dis;
	uint		w;
	uint		h;
	t_img		*img;
	char		*output;
}				t_cam;

typedef struct	s_ray
{
	float3		pos;
	float3		dir;
}				t_ray;

typedef struct	s_vec3
{
	float		x;
	float		y;
	float		z;
}				t_vec3;

typedef struct	s_buffer
{
	t_ray		ray;
	__global	t_color *img;
	__global	t_cam *cam;
	__global	uint *n_obj;
	__global	t_obj *obj;
	__global	uint *n_light;
	__global	t_light *light;
}				t_buffer;

# define get_sphere(x)		x->obj.sphere
# define get_plan(x)		x->obj.plan
# define get_pave(x)		x->obj.pave
# define get_cone(x)		x->obj.cone
# define get_cylinder(x)	x->obj.cylinder

#define get_distance(a, b)		(float)(sqrt(pown(a.x - b.x, 2) + pown(a.y - b.y, 2) + pown(a.z - b.z, 2)))
#define scalar_vectors(a, b)	(float)(a.x * b.x + a.y * b.y + a.z * b.z)
#define get_vector_norm(a)		sqrt(a->x * a->x + a->y * a->y + a->z * a->z)
#define get_vectors_angle(a, b)	scalar_vectors(a, b) / (get_vector_norm(a) * get_vector_norm(b))
#define get_distance(a, b)		sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y) + (a.z - b.z) * (a.z - b.z))
#define new_vector(x, y, z)		(float3){x, y, z}
#define add_vectors(a, b)		(float3){a.x + b.x, a.y + b.y, a.z + b.z}
#define sub_vectors(a, b)		(float3){a.x - b.x, a.y - b.y, a.z - b.z}
#define mult_vectors(a, b)		(float3){a.x * b.x, a.y * b.y, a.z * b.z}
#define mult_vector(a, b)		(float3){a.x * b, a.y * b, a.z * b}

#define SPHERE		1
#define CONE		2
#define PLAN		3
#define CYLINDER	4
#define PAVE		5

#define PI			3.1415926535

t_color	raytrace_ray(t_buffer *buffer, uint reflect);

inline float3	get_reflection_vector(float3 norm, float3 dir)
{
	return (sub_vectors(dir, mult_vector(mult_vector(norm, scalar_vectors(dir, norm)), 2)));
}

inline t_color	add_colors(t_color a, t_color b)
{
	t_color	c;

	if (a.r + b.r < 256)
	{
		if (a.r + b.r >= 0)
			c.r = a.r + b.r;
		else
			c.r = 0;
	}
	else
		c.r = 255;
	if (a.g + b.g < 256)
	{
		if (a.g + b.g >= 0)
			c.g = a.g + b.g;
		else
			c.g = 0;
	}
	else
		c.g = 255;
	if (a.b + b.b < 256)
	{
		if (a.b + b.b >= 0)
			c.b = a.b + b.b;
		else
			c.b = 0;
	}
	else
		c.b = 255;
	if (a.a + b.a < 256)
	{
		if (a.a + b.a >= 0)
			c.a = a.a + b.a;
		else
			c.a = 0;
	}
	else
		c.a = 255;
	return (c);
}

inline t_color	mult_color(t_color a, float f)
{
	t_color	c;

	if (a.r * f < 256)
	{
		if (a.r * f >= 0)
			c.r = a.r * f;
		else
			c.r = 0;
	}
	else
		c.r = 255;
	if (a.g * f < 256)
	{
		if (a.g * f >= 0)
			c.g = a.g * f;
		else
			c.g = 0;
	}
	else
		c.g = 255;
	if (a.b * f < 256)
	{
		if (a.b * f >= 0)
			c.b = a.b * f;
		else
			c.b = 0;
	}
	else
		c.b = 255;
	if (a.a * f < 256)
	{
		if (a.a * f >= 0)
			c.a = a.a * f;
		else
			c.a = 0;
	}
	else
		c.a = 255;
	return (c);
}

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

inline float3	get_sphere_norm(__global t_obj *obj, float3 point)
{
	float3	ret;

	ret = sub_vectors(point, obj->pos);
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

inline float3	get_cylinder_norm(__global t_obj *obj, float3 point)
{
	float3	norm;
	float3	tmp1;
	float3	tmp2;
	float	tmp;

	tmp1 = sub_vectors(point, obj->pos);
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

inline float3	get_cone_norm(__global t_obj *obj, float3 point)
{
	float3	norm;
	float3	tmp1;
	float3	tmp2;
	float	tmp;

	tmp1 = sub_vectors(point, obj->pos);
	tmp = scalar_vectors(tmp1, get_cylinder(obj).norm);
	norm = sub_vectors(tmp1, new_vector(tmp * get_cylinder(obj).norm.x, tmp * get_cylinder(obj).norm.y, tmp * get_cylinder(obj).norm.z));
	return (norm);
}

t_color	raytrace_ray(t_buffer *buffer, uint reflect)
{
	float	prev;
	t_ray	vec;
	float3	norm;
	t_color	color = (t_color){0, 0, 0, 255};
	float3	intensity = (float3){0, 0, 0};
	float	tmp = 0;
	float	h1;
	float	h2;
	uint	i;
	uint	j;
	uint	k;

	i = 0;
	j = -1;
	prev = -1;
	while (i < *buffer->n_obj)
	{
		h1 = -1;

		if (buffer->obj[i].type == SPHERE)
			h1 = hit_sphere(&buffer->ray, &buffer->obj[i]);
		else if (buffer->obj[i].type == PLAN)
			h1 = hit_plan(&buffer->ray, &buffer->obj[i]);
		else if (buffer->obj[i].type == CYLINDER)
			h1 = hit_cylinder(&buffer->ray, &buffer->obj[i]);
		else if (buffer->obj[i].type == CONE)
			h1 = hit_cone(&buffer->ray, &buffer->obj[i]);
		if (h1 > 0.001 && (h1 < prev || prev == -1))
		{
			j = i;
			prev = h1;
		}
		i++;
	}
	if (j != -1)
	{
		i = 0;
		vec.pos = new_vector(prev * buffer->ray.dir.x + buffer->ray.pos.x, prev * buffer->ray.dir.y + buffer->ray.pos.y, prev * buffer->ray.dir.z + buffer->ray.pos.z);
		if (buffer->obj[j].type == SPHERE)
			norm = get_sphere_norm(&buffer->obj[j], vec.pos);
		else if (buffer->obj[j].type == PLAN)
			norm = get_plan((&(buffer->obj)[j])).norm;
		else if (buffer->obj[j].type == CYLINDER)
			norm = get_cylinder_norm(&buffer->obj[j], vec.pos);
		else if (buffer->obj[j].type == CONE)
			norm = get_cone_norm(&buffer->obj[j], vec.pos);
		else
			norm = get_sphere_norm(&buffer->obj[j], vec.pos);
		while (i < *buffer->n_light)
		{
			k = 0;
			while (k < *buffer->n_obj)
			{
				vec.dir = sub_vectors(buffer->light[i].pos, vec.pos);
				normalize_vector(&vec.dir);
				h1 = (buffer->light[i].pos.x - vec.pos.x) / vec.dir.x;
				if (k != j)
				{
					if (buffer->obj[k].type == SPHERE)
					{
						if ((h2 = hit_sphere(&vec, &buffer->obj[k])) >= 0 && h2 < h1)
							k = *buffer->n_obj;
					}
					else if (buffer->obj[k].type == PLAN)
					{
						if ((h2 = hit_plan(&vec, &buffer->obj[k])) >= 0 && h2 < h1)
							k = *buffer->n_obj;
					}
					else if (buffer->obj[k].type == CONE)
					{
						if ((h2 = hit_cone(&vec, &buffer->obj[k])) >= 0 && h2 < h1)
							k = *buffer->n_obj;
					}
					else if (buffer->obj[k].type == CYLINDER)
					{
						if ((h2 = hit_cylinder(&vec, &buffer->obj[k])) >= 0 && h2 < h1)
							k = *buffer->n_obj;
					}
				}
				k++;
			}
			tmp += (buffer->light[i].i.x * buffer->obj[j].ref.x);
			if (k == *buffer->n_obj)
				tmp += (buffer->light[i].i.y * buffer->obj[j].ref.y * ((scalar_vectors(vec.dir, norm) >= 0) ? scalar_vectors(vec.dir, norm) : 0));
			intensity.x += (tmp * buffer->light[i].col.r) / (float)255;
			intensity.y += (tmp * buffer->light[i].col.g) / (float)255;
			intensity.z += (tmp * buffer->light[i].col.b) / (float)255;
			i++;
		}
		if (buffer->obj[j].ref.w > 0 && reflect < 3)
		{
			vec.dir = get_reflection_vector(norm, buffer->ray.dir);
			buffer->ray = vec;
			color = mult_color(raytrace_ray(buffer, reflect + 1), buffer->obj[j].ref.w);
			tmp = buffer->obj[j].col.r * intensity.x * (1 - buffer->obj[j].ref.w);
			if (color.r + tmp < 256)
			{
				if (color.r + tmp >= 0)
					color.r += tmp;
				else
					color.r = 0;
			}
			else
				color.r = 255;
			tmp = buffer->obj[j].col.g * intensity.y * (1 - buffer->obj[j].ref.w);
			if (color.g + tmp < 256)
			{
				if (color.g + tmp >= 0)
					color.g += tmp;
				else
					color.g = 0;
			}
			else
				color.g = 255;
				tmp = buffer->obj[j].col.b * intensity.z * (1 - buffer->obj[j].ref.w);
			if (color.b + tmp < 256)
			{
				if (color.b + tmp >= 0)
					color.b += tmp;
				else
					color.b = 0;
			}
			else
				color.b = 255;
			color.a = buffer->obj[j].col.a;
		}
		else
		{
			tmp = buffer->obj[j].col.r * intensity.x * (1 - buffer->obj[j].ref.w);
			if (color.r + tmp < 256)
			{
				if (color.r + tmp >= 0)
					color.r += tmp;
				else
					color.r = 0;
			}
			else
				color.r = 255;
			tmp = buffer->obj[j].col.g * intensity.y * (1 - buffer->obj[j].ref.w);
			if (color.g + tmp < 256)
			{
				if (color.g + tmp >= 0)
					color.g += tmp;
				else
					color.g = 0;
			}
			else
				color.g = 255;
			tmp = buffer->obj[j].col.b * intensity.z * (1 - buffer->obj[j].ref.w);
			if (color.b + tmp < 256)
			{
				if (color.b + tmp >= 0)
					color.b += tmp;
				else
					color.b = 0;
			}
			else
				color.b = 255;
		}
		return (color);
	}
	return ((t_color){0, 0, 0, 255});
}

__kernel void	raytracer(__global t_color *img, __global t_cam *cam,
				__global uint *n_obj, __global t_obj *obj,
				__global uint *n_light, __global t_light *light)
{
	t_buffer	buffer = {{{0, 0, 0}, {0, 0, 0}}, img, cam, n_obj, obj, n_light, light};
	float3		rot;
	int			id = get_global_id(0);
	float		l;

	buffer.ray.dir = (float3){1, 0, 0};
	l = 2 * cam->dis * tan(cam->fov.x / 2);
	buffer.ray.dir.y = (2 * l * (id % cam->w)) / (cam->w - 1) - l;
	l = 2 * cam->dis * tan(cam->fov.y / 2);
	buffer.ray.dir.z = (2 * l * (id / cam->w)) / (cam->h - 1) - l;

	rotate_vec(&buffer.ray.dir, cam->rot);
	buffer.ray.pos = add_vectors(cam->pos, buffer.ray.dir);
	img[id] = raytrace_ray(&buffer, 0);
}
