#ifndef lol_nik_la_norme
# define lol_nik_la_norme

// #define SWITCH

#define get_sphere(x)	x->obj.sphere
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

#define ALPHA		100

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

typedef union	u_name
{
	char		*name;
	size_t		n;
}				t_name;

typedef struct	s_texture
{
	t_name		name;
	void		*img;
}				t_texture;

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
	float4		ref;
	float		refraction;
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

#endif