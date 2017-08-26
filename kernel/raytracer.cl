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

#define scalar_vectors(a, b)	a.x * b.x + a.y * b.y + a.z * b.z
#define get_vector_norm(a)		sqrt(a->x * a->x + a->y * a->y + a->z * a->z)
#define get_vectors_angle(a, b)	scalar_vectors(a, b) / (get_vector_norm(a) * get_vector_norm(b))
#define get_distance(a, b)		sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y) + (a.z - b.z) * (a.z - b.z))
#define new_vector(x, y, z)		(float3){x, y, z}
#define sub_vectors(a, b)		(float3){a.x - b.x, a.y - b.y, a.z - b.z}
#define mult_vectors(a, b)		(float3){a.x * b.x, a.y * b.y, a.z * b.z}

#define SPHERE		1
#define CONE		2
#define PLAN		3
#define CYLINDER	4
#define PAVE		5

static void	normalize_vector(float3 *vec)
{
	float	norm = get_vector_norm(vec);

	vec->x /= norm;
	vec->y /= norm;
	vec->z /= norm;
}

static void	rotate_point(float *x, float *y, float angle)
{
	float	c = cos(angle);
	float	s = sin(angle);
	float	t_x;

	t_x = *x;
	*x = *x * c - *y * s;
	*y = t_x * s + *y * c;
}

static void	rotate_vec(float3 *vec, float3 angle)
{
	rotate_point(&((t_vec3*)vec)->x, &((t_vec3*)vec)->y, angle.z);
	rotate_point(&((t_vec3*)vec)->x, &((t_vec3*)vec)->z, angle.y);
	rotate_point(&((t_vec3*)vec)->y, &((t_vec3*)vec)->z, angle.x);
}

static float		hit_sphere(t_ray *ray, __global t_obj *obj)
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

static t_color		raytrace_ray(t_ray *ray, __global uint *n_obj, __global t_obj *obj,
				__global uint *n_light, __global t_light *light)
{
	t_color	def;
	int		i;
	float	h;

	def.r = 0;
	def.g = 0;
	def.b = 0;
	def.a = 0;
	i = 0;
	h = -1;
	while (i < *n_obj)
	{
		if (obj[i].type == SPHERE)
			h = hit_sphere(ray, &obj[i]);
		if (h >= 0)
		{
			def.r = obj[i].col.a;
			def.g = obj[i].col.b;
			def.b = obj[i].col.g;
		}
		i++;
	}
	return (def);
}

__kernel void	raytracer(__global t_color *img, __global t_cam *cam,
				__global uint *n_obj, __global t_obj *obj,
				__global uint *n_light, __global t_light *light)
{
	float3	rot;
	t_ray	ray;
	int		id = get_global_id(0);

	ray.pos = cam->pos;
	ray.dir = cam->dir;
	normalize_vector(&ray.dir);
	ray.dir.x *= cam->dis;
	ray.dir.y *= cam->dis;
	ray.dir.z *= cam->dis;
	rot = cam->rot;
	rot.z += ((2 * cam->fov.x) / (cam->w - 1)) * (id % cam->w) - cam->fov.x;
	rot.y += ((2 * cam->fov.y) / (cam->w - 1)) * (id / cam->w) - cam->fov.y;
	rotate_vec(&ray.dir, rot);
	ray.pos.x += ray.dir.x;
	ray.pos.y += ray.dir.y;
	ray.pos.z += ray.dir.z;
	img[id] = raytrace_ray(&ray, n_obj, obj, n_light, light);
}
