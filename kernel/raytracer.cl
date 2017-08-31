typedef struct	s_color
{
	uchar		b;
	uchar		g;
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

typedef struct	s_obj
{
	float3		pos;
	float3		rot;
	uchar		type;
	t_color		col;
	float3		ref;
	t_hitbox	hitbox;
	t_union		obj;
}				t_obj;

typedef struct	s_light
{
	float3		pos;
	uchar4		col;
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

#define SPHERE		1
#define CONE		2
#define PLAN		3
#define CYLINDER	4
#define PAVE		5

#define PI			3.1415926535

t_color	add_colors(t_color a, t_color b)
{
	t_color	c;

	c.r = (a.r + b.r < 256) ? a.r + b.r : 255;
	c.g = (a.g + b.g < 256) ? a.g + b.g : 255;
	c.b = (a.b + b.b < 256) ? a.b + b.b : 255;
	c.a = (a.a + b.a < 256) ? a.a + b.a : 255;
	return (c);
}

t_color	mult_color(t_color a, float f)
{
	t_color	c;

	c.r = (a.r * f < 256) ? a.r * f : 255;
	c.g = (a.g * f < 256) ? a.g * f : 255;
	c.b = (a.b * f < 256) ? a.b * f : 255;
	c.a = (a.a * f < 256) ? a.a * f : 255;
	return (c);
}

void	normalize_vector(float3 *vec)
{
	float	norm = get_vector_norm(vec);

	vec->x /= norm;
	vec->y /= norm;
	vec->z /= norm;
}

void	rotate_point(float *x, float *y, float angle)
{
	float	c = cos(angle);
	float	s = sin(angle);
	float	t_x;

	t_x = *x;
	*x = *x * c - *y * s;
	*y = t_x * s + *y * c;
}

void	rotate_vec(float3 *vec, float3 angle)
{
	rotate_point(&((t_vec3*)vec)->x, &((t_vec3*)vec)->y, angle.z);
	rotate_point(&((t_vec3*)vec)->x, &((t_vec3*)vec)->z, angle.y);
	rotate_point(&((t_vec3*)vec)->y, &((t_vec3*)vec)->z, angle.x);
}

float	hit_sphere(t_ray *ray, __global t_obj *obj)
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

float3	get_sphere_norm(__global t_obj *obj, float3 point)
{
	float3	ret;

	ret = sub_vectors(obj->pos, point);
	normalize_vector(&ret);
	return (ret);
}

float	hit_plan(t_ray *ray, __global t_obj *obj)
{
	float	h;

	h = scalar_vectors(get_plan(obj).norm, ray->dir);
	if (h == 0)
		return (-42);
	return (-(scalar_vectors(get_plan(obj).norm, sub_vectors(ray->pos, obj->pos))) / h);
}

float	hit_cylinder(t_ray *ray, __global t_obj *obj)
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

float3	get_cylinder_norm(__global t_obj *obj, float3 point)
{
	float3	norm;
	float3	tmp1;
	float3	tmp2;
	float	tmp;

	tmp1 = sub_vectors(obj->pos, point);
	tmp = scalar_vectors(tmp1, get_cylinder(obj).norm);
	norm = sub_vectors(tmp1, new_vector(tmp * get_cylinder(obj).norm.x, tmp * get_cylinder(obj).norm.y, tmp * get_cylinder(obj).norm.z));
	return (norm);
}

float	hit_cone(t_ray *ray, __global t_obj *obj)
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

float3	get_cone_norm(__global t_obj *obj, float3 point)
{
	float3	norm;
	float3	tmp1;
	float3	tmp2;
	float	tmp;

	tmp1 = sub_vectors(obj->pos, point);
	tmp = scalar_vectors(tmp1, get_cylinder(obj).norm);
	norm = sub_vectors(tmp1, new_vector(tmp * get_cylinder(obj).norm.x, tmp * get_cylinder(obj).norm.y, tmp * get_cylinder(obj).norm.z));
	return (norm);
}

t_color	render_light(__global uint *n_obj, __global t_obj *obj,
					int j, t_ray *ray, float h,
					__global uint *n_light, __global t_light *light)
{
	float3	point;
	float3	norm;
	t_ray	vec;
	t_color	color = (t_color){0, 0, 0, 255};
	float	intensity;
	float	h1;
	float	h2;
	int		i;
	int		k;

	i = 0;
	intensity = 0;
	point = (float3){h * ray->dir.x + ray->pos.x, h * ray->dir.y + ray->pos.y, h * ray->dir.z + ray->pos.z};
	if (obj[j].type == SPHERE)
		norm = get_sphere_norm(&obj[j], point);
	else if (obj[j].type == PLAN)
		norm = get_plan(obj).norm;
	else if (obj[j].type == CYLINDER)
		norm = get_cylinder_norm(&obj[j], point);
	else if (obj[j].type == CONE)
		norm = get_cone_norm(&obj[j], point);
	else
		norm = get_sphere_norm(&obj[j], point);
	while (i < *n_light)
	{
		intensity += (light[i].i.x * obj[j].ref.x) / get_distance(point, light->pos);
		k = 0;
		while (k < *n_obj)
		{
			vec.pos = new_vector(h * ray->dir.x + ray->pos.x, h * ray->dir.y + ray->pos.y, h * ray->dir.z + ray->pos.z);
			vec.dir = sub_vectors(light[i].pos, vec.pos);
			normalize_vector(&vec.dir);
			h1 = (light[i].pos.x - vec.pos.x) / vec.dir.x;
			if (k != j)
			{
				if (obj[k].type == SPHERE)
				{
					if ((h2 = hit_sphere(&vec, &obj[k])) >= 0 && h2 < h1)
						k = *n_obj;
				}
				else if (obj[k].type == PLAN)
				{
					if ((h2 = hit_plan(&vec, &obj[k])) >= 0 && h2 < h1)
						k = *n_obj;
				}
				else if (obj[k].type == CONE)
				{
					if ((h2 = hit_cone(&vec, &obj[k])) >= 0 && h2 < h1)
						k = *n_obj;
				}
				else if (obj[k].type == CYLINDER)
				{
					if ((h2 = hit_cylinder(&vec, &obj[k])) >= 0 && h2 < h1)
						k = *n_obj;
				}
			}
			k++;
		}
		if (k == *n_obj)
			intensity += (light[i].i.y * obj[j].ref.y * scalar_vectors(ray->dir, norm)) / get_distance(point, light->pos);
		// else
		// 	printf("%d/%d\n", k, *n_obj);
		i++;
	}
	// printf("i=%d amb=%f color(%u %u %u %u) pos(%f %f %f)\n", i, light[0].i.x, light[0].col.r, light[0].col.g, light[0].col.b, light[0].col.a, light[0].pos.x, light[0].pos.y, light[0].pos.z);
	return (mult_color(obj[j].col, intensity));
}

t_color	raytrace_ray(t_ray *ray, __global uint *n_obj, __global t_obj *obj,
					__global uint *n_light, __global t_light *light)
{
	int		i;
	int		j;
	float	h;
	float	prev;

	i = 0;
	j = -1;
	prev = -1;
	while (i < *n_obj)
	{
		h = -1;

		if (obj[i].type == SPHERE)
			h = hit_sphere(ray, &obj[i]);
		else if (obj[i].type == PLAN)
			h = hit_plan(ray, &obj[i]);
		else if (obj[i].type == CYLINDER)
			h = hit_cylinder(ray, &obj[i]);
		else if (obj[i].type == CONE)
			h = hit_cone(ray, &obj[i]);
		if (h >= 0 && (h < prev || prev == -1))
		{
			j = i;
			prev = h;
		}
		i++;
	}
	if (j != -1)
		return (render_light(n_obj, obj, j, ray, prev, n_light, light));
	return ((t_color){0, 0, 0, 255});
}

__kernel void	raytracer(__global t_color *img, __global t_cam *cam,
				__global uint *n_obj, __global t_obj *obj,
				__global uint *n_light, __global t_light *light)
{
	float3	rot;
	t_ray	ray;
	int		id = get_global_id(0);
	float	l;

	// ray.pos = cam->pos;
	// ray.dir = cam->dir;
	// rot = cam->rot;
	// // ray.dir.y += ((id % cam->w) * ((2 * cam->dis) / ((cam->w - 1) * cos(cam->fov.x))) - cam->dis / cos(cam->fov.x));
	// // ray.dir.z += ((id / cam->w) * ((2 * cam->dis) / ((cam->h - 1) * cos(cam->fov.y))) - cam->dis / cos(cam->fov.y));
	// rot.x -= 0;
	// rot.z += ((cam->fov.x) / (cam->w - 1)) * (id % cam->w) - cam->fov.x / 2;
	// rot.y += ((cam->fov.y) / (cam->h - 1)) * (id / cam->w) - cam->fov.y / 2;
	// rotate_vec(&ray.dir, rot);
	// // ray.pos.x += ray.dir.x;
	// // ray.pos.y += ray.dir.y;
	// // ray.pos.z += ray.dir.z;

	ray.dir = (float3){1, 0, 0};
	l = 2 * cam->dis * tan(cam->fov.x / 2);
	ray.dir.y = (2 * l * (id % cam->w)) / (cam->w - 1) - l;
	l = 2 * cam->dis * tan(cam->fov.y / 2);
	ray.dir.z = (2 * l * (id / cam->w)) / (cam->h - 1) - l;
	
	// printf("z=%f\n", ray.dir.z);
	// rotate_vec(&ray.dir, (float3){0,
	// ((cam->fov.y) / (cam->h - 1)) * (id / cam->w) - cam->fov.y / 2,
	// ((cam->fov.x) / (cam->w - 1)) * (id % cam->w) - cam->fov.x / 2});
	// ray.pos = cam->pos;
	ray.pos = add_vectors(cam->pos, ray.dir);
	img[id] = raytrace_ray(&ray, n_obj, obj, n_light, light);
}
