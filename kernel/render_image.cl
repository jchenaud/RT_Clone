typedef struct	s_color
{
	uchar		g;
	uchar		b;
	uchar		r;
	uchar		a;
}				t_color;

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

typedef struct	s_obj
{
	float3		pos;
	float3		rot;
	uchar		type;
	t_color		col;
	float4		ref;
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
	void		*img;
	char		*output;
}				t_cam;

typedef struct	s_vec3
{
	float		x;
	float		y;
	float		z;
}				t_vec3;

typedef struct	s_ray
{
	float3		pos;
	float3		dir;
	float		f;
}				t_ray;

typedef struct	s_intersec
{
	int			obj;
	float		h;
}				t_intersec;

#define get_sphere(x)		x->obj.sphere
#define get_plan(x)		x->obj.plan
#define get_pave(x)		x->obj.pave
#define get_cone(x)		x->obj.cone
#define get_cylinder(x)	x->obj.cylinder

#define get_distance(a, b)		(float)(sqrt(pown(a.x - b.x, 2) + pown(a.y - b.y, 2) + pown(a.z - b.z, 2)))
#define scalar_vectors(a, b)	(float)(a.x * b.x + a.y * b.y + a.z * b.z)
#define get_vector_norm(a)		sqrt(a->x * a->x + a->y * a->y + a->z * a->z)
#define get_vectors_angle(a, b)	scalar_vectors(a, b) / (get_vector_norm(a) * get_vector_norm(b))
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

#define ALPHA		10

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

inline void	normalize_global_vector(__global float3 *vec)
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
	float	tmp;

	tmp1 = sub_vectors(point, obj->pos);
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
	float	tmp;
	float	h_tmp;
	float	h;
	int		id = *p * get_global_id(0) + *j;
	uint	i = 0;
	uint	k;

	img = &img[id / *p];
	intersec = &intersec[id];
	ray = &ray[id];
	normalize_global_vector(&ray->dir);
	if ((ray->dir.x == 0 && ray->dir.y == 0 && ray->dir.z == 0) ||
	intersec->h <= 0.01 || intersec->obj == -1 || ray->f == 0)
	{
		*img = add_colors(*img, mult_color((t_color){0, 0, 0, 255}, ray->f));
		return ;
	}
	vec.pos = (float3){intersec->h * ray->dir.x + ray->pos.x, intersec->h * ray->dir.y + ray->pos.y, intersec->h * ray->dir.z + ray->pos.z};
	if (obj[intersec->obj].type == SPHERE)
		norm = get_sphere_norm(&obj[intersec->obj], vec.pos);
	else if (obj[intersec->obj].type == PLAN)
		norm = get_plan((&obj[intersec->obj])).norm;
	else if (obj[intersec->obj].type == CYLINDER)
		norm = get_cylinder_norm(&obj[intersec->obj], vec.pos);
	else if (obj[intersec->obj].type == CONE)
		norm = get_cone_norm(&obj[intersec->obj], vec.pos);
	else
		norm = get_sphere_norm(&obj[intersec->obj], vec.pos);
	normalize_vector(&norm);
	while (i < *n_light)
	{
		vec.dir = sub_vectors(light[i].pos, vec.pos);
		normalize_vector(&vec.dir);
		h_tmp = (light[i].pos.x - vec.pos.x) / vec.dir.x;
		tmp = 0;
		k = 0;
		while (k < *n_obj)
		{
			// if ((int)k != intersec->obj)
			// {
				if (obj[k].type == SPHERE)
				{
					if ((h = hit_sphere(&vec, &obj[k])) > 0.01 && h < h_tmp)
						k = *n_obj;
				}
				else if (obj[k].type == PLAN)
				{
					if ((h = hit_plan(&vec, &obj[k])) > 0.01 && h < h_tmp)
						k = *n_obj;
				}
				else if (obj[k].type == CONE)
				{
					if ((h = hit_cone(&vec, &obj[k])) > 0.01 && h < h_tmp)
						k = *n_obj;
				}
				else if (obj[k].type == CYLINDER)
				{
					if ((h = hit_cylinder(&vec, &obj[k])) > 0.01 && h < h_tmp)
						k = *n_obj;
				}
			// }
			k++;
		}
		tmp += (light[i].i.x * obj[intersec->obj].ref.x);
		if (k == *n_obj)
		{
			tmp += (light[i].i.y * obj[intersec->obj].ref.y * ((scalar_vectors(vec.dir, norm) >= 0) ? scalar_vectors(vec.dir, norm) : 0));
			vec.dir = sub_vectors(vec.dir, mult_vector(mult_vector(norm, scalar_vectors(vec.dir, norm)), 2));
			normalize_vector(&vec.dir);
			fact = add_vectors(fact, mult_vector(new_vector(1, 1, 1), (light[i].i.z * obj[intersec->obj].ref.z * pow(scalar_vectors(ray->dir, vec.dir), ALPHA))));
		}
		fact.x += (tmp * light[i].col.r) / (float)255;
		fact.y += (tmp * light[i].col.g) / (float)255;
		fact.z += (tmp * light[i].col.b) / (float)255;
		i++;
	}
	color = mult_color(obj[intersec->obj].col, (1 - obj[intersec->obj].ref.w) * ((float)obj[intersec->obj].col.a / (float)255));
	if (obj[intersec->obj].ref.w > 0)
	{
		if (color.r * fact.x < 256)
		{
			if (color.r * fact.x >= 0)
				color.r *= fact.x;
			else
				color.r = 0;
		}
		else
			color.r = 255;
		if (color.g * fact.y < 256)
		{
			if (color.g * fact.y >= 0)
				color.g *= fact.y;
			else
				color.g = 0;
		}
		else
			color.g = 255;
		if (color.b * fact.z < 256)
		{
			if (color.b * fact.z >= 0)
				color.b *= fact.z;
			else
				color.b = 0;
		}
		else
			color.b = 255;
	}
	*img = add_colors(*img, mult_color(color, ray->f));
}
