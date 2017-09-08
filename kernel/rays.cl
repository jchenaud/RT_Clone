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

inline float3	get_reflection_vector(float3 norm, float3 dir)
{
	return (sub_vectors(dir, mult_vector(mult_vector(norm, scalar_vectors(dir, norm)), 2)));
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

inline float3	get_sphere_norm(__global t_obj *obj, float3 point)
{
	float3	ret;

	ret = sub_vectors(point, obj->pos);
	normalize_vector(&ret);
	return (ret);
}

inline float3	get_plan_norm(__global t_obj *obj, float3 point)
{
	return (get_plan(obj).norm);
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

__kernel void	calc_rays(__global t_ray *new, __global t_ray *ray, __global t_intersec *intersec,
						__global uint *n_obj, __global t_obj *obj)
{
	int			id = get_global_id(0);
	float3		point;
	float3		norm;

	ray = &ray[id];
	new = &new[id * 2];
	intersec = &intersec[id];
	if ((ray->dir.x == 0 && ray->dir.y == 0 && ray->dir.z == 0) ||
	intersec->h == -1 || intersec->obj == -1 || ray->f <= 0)
	{
		new[0] = (t_ray){{0, 0, 0}, {0, 0, 0}, 0};
		new[1] = (t_ray){{0, 0, 0}, {0, 0, 0}, 0};
		return ;
	}
	// normalize_global_vector(&ray->dir);
	point = (float3){intersec->h * ray->dir.x + ray->pos.x, intersec->h * ray->dir.y + ray->pos.y, intersec->h * ray->dir.z + ray->pos.z};
	obj = &obj[intersec->obj];
	if (obj->type == SPHERE)
		norm = get_sphere_norm(obj, point);
	else if (obj->type == PLAN)
		norm = get_plan_norm(obj, point);
	else if (obj->type == CONE)
		norm = get_cone_norm(obj, point);
	else if (obj->type == CYLINDER)
		norm = get_cylinder_norm(obj, point);
	else
		norm = get_sphere_norm(obj, point);
	new[0].pos = point;
	new[1].pos = point;
	new[0].dir = get_reflection_vector(norm, ray->dir);
	normalize_global_vector(&new[0].dir);
	new[1].dir = ray->dir;
	new[0].f = ray->f * obj->ref.w;
	new[1].f = (ray->f * (255 - obj->col.a) / (float)255);
}
