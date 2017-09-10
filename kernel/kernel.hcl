#ifndef lol_nik_la_norme
# define lol_nik_la_norme

typedef struct	s_color
{
	uchar		g;
	uchar		b;
	uchar		r;
	uchar		a;
}				t_color;

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