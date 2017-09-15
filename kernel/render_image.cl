#include "kernel/kernel.hcl"

inline t_color	add_colors(t_color a, t_color b)
{
	return ((t_color){
	(a.r + b.r < 0) ? 0 : ((a.r + b.r > 255) ? 255 : a.r + b.r),
	(a.b + b.b < 0) ? 0 : ((a.b + b.b > 255) ? 255 : a.b + b.b),
	(a.g + b.g < 0) ? 0 : ((a.g + b.g > 255) ? 255 : a.g + b.g),
	255});
}

inline t_color	mult_color(t_color a, float f)
{
	return ((t_color){
	(a.r * f < 0) ? 0 : ((a.r * f > 255) ? 255 : a.r * f),
	(a.g * f < 0) ? 0 : ((a.g * f > 255) ? 255 : a.g * f),
	(a.b * f < 0) ? 0 : ((a.b * f > 255) ? 255 : a.b * f),
	255});
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

inline char		check_hitbox(__global t_hitbox *hitbox, t_ray *ray, __global float3 *center, float *h)
{
	float3	point = (float3){ray->dir.x * *h + ray->pos.x, ray->dir.y * *h + ray->pos.y, ray->dir.z * *h + ray->pos.z};

	point = sub_vectors(point, (*center));
	rotate_vec(&point, (float3){-hitbox->rot.x, -hitbox->rot.y, -hitbox->rot.z});
	point = add_vectors(point, (*center));
	if (point.x < hitbox->min.x || point.x > hitbox->max.x ||
		point.y < hitbox->min.y || point.y > hitbox->max.y ||
		point.z < hitbox->min.z || point.z > hitbox->max.z)
		return ((hitbox->type & INVISIBLE) ? 1 : 0);
	return ((hitbox->type & INVISIBLE) ? 0 : 1);
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
	h1 = (check_hitbox(&obj->hitbox, ray, &obj->pos, &h1)) ? h1 : -1;
	h2 = (check_hitbox(&obj->hitbox, ray, &obj->pos, &h2)) ? h2 : -1;
	if (h1 < MARGE)
		return (h2);
	if (h2 < MARGE)
		return (h1);
	return ((h1 < h2) ? h1 : h2);
}

inline float3	get_sphere_norm(__global t_obj *obj, float3 *point)
{
	float3	ret;

	ret = sub_vectors((*point), obj->pos);
	normalize_vector(&ret);
	return (ret);
}

inline float	hit_plan(t_ray *ray, __global t_obj *obj)
{
	float	h;

	h = scalar_vectors(get_plan(obj).norm, ray->dir);
	h = (check_hitbox(&obj->hitbox, ray, &obj->pos, &h)) ? h : -1;
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
	h1 = (check_hitbox(&obj->hitbox, ray, &obj->pos, &h1)) ? h1 : -1;
	h2 = (check_hitbox(&obj->hitbox, ray, &obj->pos, &h2)) ? h2 : -1;
	if (h1 < MARGE)
		return (h2);
	if (h2 < MARGE)
		return (h1);
	return ((h1 < h2) ? h1 : h2);
}

inline float3	get_cylinder_norm(__global t_obj *obj, float3 *point)
{
	float3	norm;
	float3	tmp1;
	float	tmp;

	tmp1 = sub_vectors((*point), obj->pos);
	tmp = scalar_vectors(tmp1, get_cylinder(obj).norm);
	norm = sub_vectors(tmp1, new_vector(tmp * get_cylinder(obj).norm.x, tmp * get_cylinder(obj).norm.y, tmp * get_cylinder(obj).norm.z));
	normalize_vector(&norm);
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
	h1 = (check_hitbox(&obj->hitbox, ray, &obj->pos, &h1)) ? h1 : -1;
	h2 = (check_hitbox(&obj->hitbox, ray, &obj->pos, &h2)) ? h2 : -1;
	if (h1 < 0)
		return (h2);
	if (h2 < 0)
		return (h1);
	return ((h1 < h2) ? h1 : h2);
}

inline float3	get_cone_norm(__global t_obj *obj, float3 *point)
{
	float3	norm;
	float3	tmp1;
	float	tmp;

	tmp1 = sub_vectors((*point), obj->pos);
	tmp = scalar_vectors(tmp1, get_cylinder(obj).norm);
	norm = sub_vectors(tmp1, new_vector(tmp * get_cylinder(obj).norm.x, tmp * get_cylinder(obj).norm.y, tmp * get_cylinder(obj).norm.z));
	normalize_vector(&norm);
	return (norm);
}

float2			get_sphere_uv(__global t_obj *obj, float3 point)
{
	float2	uv;
	float	r;

	rotate_vec(&point, (float3){-obj->rot.x, -obj->rot.y, -obj->rot.z});
	r = get_sphere(obj).rad * cos(asin((point.z - obj->pos.z) / get_sphere(obj).rad));
	uv.y = (obj->pos.z - point.z) / (2 * get_sphere(obj).rad) + 0.5;
	uv.x = (point.y - obj->pos.y >= 0) ?
	0.5 - acos((point.x - obj->pos.x) / r) / (2 * PI) :
	0.5 - (2 * PI - acos((point.x - obj->pos.x) / r)) / (2 * PI);
	uv.x += (uv.x < 0) ? 1 : 0;
	return (uv);
}

float2			get_plan_uv(__global t_obj *obj, float3 point, __global t_img *img)
{
	float2	uv;
	float	norm = get_vector_norm((&get_plan(obj).norm));

	rotate_vec(&point, (float3){
	0 - acos(get_plan(obj).norm.z / norm),
	PI / 2 - acos(get_plan(obj).norm.x / norm),
	PI / 2 - acos(get_plan(obj).norm.y / norm)});
	uv.x = (point.x >= 0) ?
	fmod(ft_abs(point.x / 10), 1) :
	1 - fmod(ft_abs(point.x / 10), 1);
	uv.y = (point.y >= 0) ?
	fmod(ft_abs(point.y / 10), 1) :
	1 - fmod(ft_abs(point.y / 10), 1);
	return (uv);
}

float2			get_cylinder_uv(__global t_obj *obj, float3 point, __global t_img *img)
{
	float2	uv;
	float	norm = get_vector_norm((&get_plan(obj).norm));

	rotate_vec(&point, (float3){
	0 - acos(get_plan(obj).norm.z / norm),
	PI / 2 - acos(get_plan(obj).norm.x / norm),
	PI / 2 - acos(get_plan(obj).norm.y / norm)});
	uv.x = (point.y - obj->pos.y >= 0) ?
	0.5 - acos((point.x - obj->pos.x) / get_cylinder(obj).rad) / (2 * PI) :
	0.5 - (2 * PI - acos((point.x - obj->pos.x) / get_cylinder(obj).rad)) / (2 * PI);
	uv.x += (uv.x < 0) ? 1 : 0;
	point.z /= 10;
	uv.y = fmod(ft_abs(point.z), 1);
	return (uv);
}

float2			get_cone_uv(__global t_obj *obj, float3 point, __global t_img *img)
{
	float2	uv;
	float	norm = get_vector_norm((&get_plan(obj).norm));
	float	r;

	rotate_vec(&point, (float3){
	0 - acos(get_plan(obj).norm.z / norm),
	PI / 2 - acos(get_plan(obj).norm.x / norm),
	PI / 2 - acos(get_plan(obj).norm.y / norm)});
	r = sqrt(pown(point.x - obj->pos.x, 2) + pown(point.y - obj->pos.y, 2));
	uv.x = (point.y - obj->pos.y >= 0) ?
	0.5 - acos((point.x - obj->pos.x) / r) / (2 * PI) :
	0.5 - (2 * PI - acos((point.x - obj->pos.x) / r)) / (2 * PI);
	uv.x += (uv.x < 0) ? 1 : 0;
	point.z /= 10;
	uv.y = fmod(ft_abs(point.z), 1);
	return (uv);
}

__global t_img	*get_texture(__global t_img *textures, int i)
{
	size_t	size;

	while (i > 0)
	{
		size = sizeof(t_img) + sizeof(t_color) * textures->w * textures->h;
		textures = (__global void*)textures + size;
		i--;
	}
	return (textures);
}

t_color			get_color(__global t_img *textures, __global t_obj *obj, float3 *point, int i)
{
	__global t_img	*img;
	t_color			color = (t_color){0, 0, 0, 255};
	float2			uv;

	if (obj->mat.textures[i].n < 0)
		return (obj->mat.col);
	img = get_texture(textures, obj->mat.textures[i].n);
	if (obj->type == SPHERE)
		uv = get_sphere_uv(obj, *point);
	else if (obj->type == PLAN)
		uv = get_plan_uv(obj, *point, img);
	else if (obj->type == CYLINDER)
		uv = get_cylinder_uv(obj, *point, img);
	else if (obj->type == CONE)
		uv = get_cone_uv(obj, *point, img);
	else
		uv = (float2){0, 0};
	uv.x = (isnan(uv.x)) ? 0 : (isinf(uv.x) ? 0 : uv.x);
	uv.y = (isnan(uv.y)) ? 0 : (isinf(uv.y) ? 0 : uv.y);
	color = ((__global t_color*)((__global void*)img + sizeof(t_img)))[(int)(uv.y * (img->h - 1)) * img->w + (int)(uv.x * (img->w - 1))];
	return (color);
}

__kernel void	render_img(__global t_color *img, __global size_t *p,
				__global t_ray *ray, __global t_intersec *intersec,
				__global uint *n_obj, __global t_obj *obj,
				__global uint *n_light, __global t_light *light,
				__global t_img *textures, __global size_t *j)
{
	t_color	color = (t_color){0, 0, 0, 255};
	t_ray	vec;
	float3	norm;
	float3	fact = (float3){0, 0, 0};
	float	alpha;
	float	h_tmp;
	float	tmp;
	float	h;
	int		id = *p * get_global_id(0) + *j;
	uint	i = 0;
	uint	k;

	img = &img[id / *p];
	intersec = &intersec[id];
	ray = &ray[id];
	if ((ray->dir.x == 0 && ray->dir.y == 0 && ray->dir.z == 0) ||
	intersec->h <= MARGE || intersec->obj == -1 || ray->f == 0)
	{
		*img = add_colors(*img, (t_color){0, 0, 0, 255});
		return ;
	}
	vec.pos = (float3){intersec->h * ray->dir.x + ray->pos.x, intersec->h * ray->dir.y + ray->pos.y, intersec->h * ray->dir.z + ray->pos.z};
#ifdef SWITCH
	switch (obj[intersec->obj].type)
	{
		case SPHERE:
			norm = get_sphere_norm(&obj[intersec->obj], &vec.pos);
		break;
		case PLAN:
			norm = get_plan((&obj[intersec->obj])).norm;
		break;
		case CYLINDER:
			norm = get_cylinder_norm(&obj[intersec->obj], &vec.pos);
		break;
		case CONE:
			norm = get_cone_norm(&obj[intersec->obj], &vec.pos);
		break;
	}
#else
	if (obj[intersec->obj].type == SPHERE)
		norm = get_sphere_norm(&obj[intersec->obj], &vec.pos);
	else if (obj[intersec->obj].type == PLAN)
		norm = get_plan((&obj[intersec->obj])).norm;
	else if (obj[intersec->obj].type == CYLINDER)
		norm = get_cylinder_norm(&obj[intersec->obj], &vec.pos);
	else if (obj[intersec->obj].type == CONE)
		norm = get_cone_norm(&obj[intersec->obj], &vec.pos);
	else
		norm = get_sphere_norm(&obj[intersec->obj], &vec.pos);
#endif
	while (i < *n_light)
	{
		vec.dir = sub_vectors(light[i].pos, vec.pos);
		normalize_vector(&vec.dir);
		h_tmp = (light[i].pos.x - vec.pos.x) / vec.dir.x;
		tmp = 0;
		k = 0;
		alpha = 1;
		while (k < *n_obj)
		{
#ifdef SWITCH
			switch (obj[k].type)
			{
				case SPHERE:
					if ((h = hit_sphere(&vec, &obj[k])) > MARGE && h < h_tmp)
					{
						if (obj[k].mat.col.a != 255)
							alpha *= ((255 - obj[k].mat.col.a) / (float)255);
						else
							k = *n_obj;
					}
				break;
				case PLAN:
					if ((h = hit_plan(&vec, &obj[k])) > MARGE && h < h_tmp)
					{
						if (obj[k].mat.col.a != 255)
							alpha *= ((255 - obj[k].mat.col.a) / (float)255);
						else
							k = *n_obj;
					}
				break;
				case CYLINDER:
					if ((h = hit_cylinder(&vec, &obj[k])) > MARGE && h < h_tmp)
					{
						if (obj[k].mat.col.a != 255)
							alpha *= ((255 - obj[k].mat.col.a) / (float)255);
						else
							k = *n_obj;
					}
				break;
				case CONE:
					if ((h = hit_cone(&vec, &obj[k])) > MARGE && h < h_tmp)
					{
						if (obj[k].mat.col.a != 255)
							alpha *= ((255 - obj[k].mat.col.a) / (float)255);
						else
							k = *n_obj;
					}
				break;
			}
#else
			if (obj[k].type == SPHERE)
			{
				if ((h = hit_sphere(&vec, &obj[k])) > MARGE && h < h_tmp)
				{
					if (obj[k].mat.col.a != 255)
						alpha *= ((255 - obj[k].mat.col.a) / (float)255);
					else
						k = *n_obj;
				}
			}
			else if (obj[k].type == PLAN)
			{
				if ((h = hit_plan(&vec, &obj[k])) > MARGE && h < h_tmp)
				{
					if (obj[k].mat.col.a != 255)
						alpha *= ((255 - obj[k].mat.col.a) / (float)255);
					else
						k = *n_obj;
				}
			}
			else if (obj[k].type == CONE)
			{
				if ((h = hit_cone(&vec, &obj[k])) > MARGE && h < h_tmp)
				{
					if (obj[k].mat.col.a != 255)
						alpha *= ((255 - obj[k].mat.col.a) / (float)255);
					else
						k = *n_obj;
				}
			}
			else if (obj[k].type == CYLINDER)
			{
				if ((h = hit_cylinder(&vec, &obj[k])) > MARGE && h < h_tmp)
				{
					if (obj[k].mat.col.a != 255)
						alpha *= ((255 - obj[k].mat.col.a) / (float)255);
					else
						k = *n_obj;
				}
			}
#endif
			k++;
		}
		tmp = (light[i].i.x * obj[intersec->obj].mat.ref.x);
		if (k == *n_obj)
		{
			tmp += (light[i].i.y * obj[intersec->obj].mat.ref.y * ((scalar_vectors(vec.dir, norm) >= 0) ? scalar_vectors(vec.dir, norm) : 0));
			vec.dir = sub_vectors(vec.dir, mult_vector(mult_vector(norm, scalar_vectors(vec.dir, norm)), 2));
			normalize_vector(&vec.dir);
			fact = add_vectors(fact, mult_vector(new_vector(1, 1, 1), (light[i].i.z * obj[intersec->obj].mat.ref.z * pow(scalar_vectors(mult_vector(ray->dir, 0.99), vec.dir), ALPHA))));
		}
		tmp *= alpha;
		fact.x += (tmp * light[i].col.r) / (float)255;
		fact.y += (tmp * light[i].col.g) / (float)255;
		fact.z += (tmp * light[i].col.b) / (float)255;
		i++;
	}
	color = mult_color(get_color(textures, &obj[intersec->obj], &vec.pos, 0), (1 - obj[intersec->obj].mat.ref.w) * (obj[intersec->obj].mat.col.a / (float)255));
	fact.x = (isnan(fact.x)) ? 0 : ((isinf(fact.x)) ? 0 : fact.x);
	fact.y = (isnan(fact.y)) ? 0 : ((isinf(fact.y)) ? 0 : fact.y);
	fact.z = (isnan(fact.z)) ? 0 : ((isinf(fact.z)) ? 0 : fact.z);
	color.r = (color.r * fact.x < 0) ? 0 : ((color.r * fact.x > 255) ? 255 : color.r * fact.x);
	color.g = (color.g * fact.y < 0) ? 0 : ((color.g * fact.y > 255) ? 255 : color.g * fact.y);
	color.b = (color.b * fact.z < 0) ? 0 : ((color.b * fact.z > 255) ? 255 : color.b * fact.z);
	color.a = 255;
	*img = add_colors(*img, invert_color(mult_color(color, ray->f)));
}
