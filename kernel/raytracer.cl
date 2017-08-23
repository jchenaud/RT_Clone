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
	uchar4		col;
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

__kernel void	raytracer(__global t_color *img, __global t_cam *cam,
				__global uint *n_obj, __global t_obj *obj,
				__global uint *n_light, __global t_light *light)
{
	t_color	def;
	int		id = get_global_id(0);

	def.r = 255;
	def.g = 0;
	def.b = 0;
	def.a = 0;
	img[id] = def;
}
