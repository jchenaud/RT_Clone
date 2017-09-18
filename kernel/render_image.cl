#include "kernel/kernel.hcl"

inline t_color	add_colors(t_color a, t_color b)
{
	return ((t_color){
	(a.r + b.r < 0) ? 0 : ((a.r + b.r > 255) ? 255 : a.r + b.r),
	(a.g + b.g < 0) ? 0 : ((a.g + b.g > 255) ? 255 : a.g + b.g),
	(a.b + b.b < 0) ? 0 : ((a.b + b.b > 255) ? 255 : a.b + b.b),
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

	point = sub_vectors(point, obj->pos);
	rotate_vec(&point, (float3){
	0 - acos(get_plan(obj).norm.z / norm) + obj->rot.x,
	PI / 2 - acos(get_plan(obj).norm.x / norm) + obj->rot.y,
	PI / 2 - acos(get_plan(obj).norm.y / norm) + obj->rot.z});
	point = add_vectors(point, obj->pos);
	point.x /= obj->mat.size.x;
	point.y /= obj->mat.size.y;
	uv.x = (point.x >= 0) ?
	fmod(ft_abs(point.x), 1) :
	1 - fmod(ft_abs(point.x), 1);
	uv.y = (point.y >= 0) ?
	fmod(ft_abs(point.y), 1) :
	1 - fmod(ft_abs(point.y), 1);
	return (uv);
}

float2			get_cylinder_uv(__global t_obj *obj, float3 point, __global t_img *img)
{
	float2	uv;
	float	norm = get_vector_norm((&get_plan(obj).norm));

	point = sub_vectors(point, obj->pos);
	rotate_vec(&point, (float3){
	0 - acos(get_plan(obj).norm.z / norm),
	PI / 2 - acos(get_plan(obj).norm.x / norm),
	PI / 2 - acos(get_plan(obj).norm.y / norm)});
	point = add_vectors(point, obj->pos);
	uv.x = (point.y - obj->pos.y >= 0) ?
	0.5 - acos((point.x - obj->pos.x) / get_cylinder(obj).rad) / (2 * PI) :
	0.5 - (2 * PI - acos((point.x - obj->pos.x) / get_cylinder(obj).rad)) / (2 * PI);
	uv.x += (uv.x < 0) ? 1 : 0;
	point.z /= obj->mat.size.y;
	uv.y = fmod(ft_abs(point.z), 1);
	return (uv);
}

float2			get_cone_uv(__global t_obj *obj, float3 point, __global t_img *img)
{
	float2	uv;
	float	norm = get_vector_norm((&get_plan(obj).norm));
	float	r;

	point = sub_vectors(point, obj->pos);
	rotate_vec(&point, (float3){
	0 - acos(get_plan(obj).norm.z / norm),
	PI / 2 - acos(get_plan(obj).norm.x / norm),
	PI / 2 - acos(get_plan(obj).norm.y / norm)});
	point = add_vectors(point, obj->pos);
	r = sqrt(pown(point.x - obj->pos.x, 2) + pown(point.y - obj->pos.y, 2));
	uv.x = (point.y - obj->pos.y >= 0) ?
	0.5 - acos((point.x - obj->pos.x) / r) / (2 * PI) :
	0.5 - (2 * PI - acos((point.x - obj->pos.x) / r)) / (2 * PI);
	uv.x += (uv.x < 0) ? 1 : 0;
	point.z /= obj->mat.size.y;
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
		return ((t_color){obj->mat.col.r, obj->mat.col.b, obj->mat.col.g, obj->mat.col.a});
	// printf("size=(%f %f)\n", obj->mat.size.x, obj->mat.size.y);
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

float3			get_normal_map(__global t_img *textures, __global t_obj *obj, float3 *point)
{
	__global t_img	*img;
	t_color			color;
	float3			norm = (float3){0, 0, 0};
	float2			uv;

	if (obj->mat.textures[3].n < 0)
		return ((float3){0, 0, 1});
	img = get_texture(textures, obj->mat.textures[3].n);
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
	norm = (float3){(color.r - 128) / (float)255, (color.g - 128) / (float)255, (color.b - 128) / (float)255};
	normalize_vector(&norm);
	return (norm);
}

float3			get_norm(__global t_img *textures, __global t_obj *obj, float3 *point)
{
	float3	norm_obj;
	float3	norm_map;

#ifdef SWITCH
	switch (obj->type)
	{
		case SPHERE:
			norm_obj = get_sphere_norm(obj, point);
		break;
		case PLAN:
			norm_obj = get_plan(obj).norm;
		break;
		case CYLINDER:
			norm_obj = get_cylinder_norm(obj, point);
		break;
		case CONE:
			norm_obj = get_cone_norm(obj, point);
		break;
	}
#else
	if (obj->type == SPHERE)
		norm_obj = get_sphere_norm(obj, point);
	else if (obj->type == PLAN)
		norm_obj = get_plan(obj).norm;
	else if (obj->type == CYLINDER)
		norm_obj = get_cylinder_norm(obj, point);
	else if (obj->type == CONE)
		norm_obj = get_cone_norm(obj, point);
	else
		norm_obj = get_sphere_norm(obj, point);
#endif
	normalize_vector(&norm_obj);
	norm_map = get_normal_map(textures, obj, point);
	rotate_vec(&norm_obj, (float3){
	0 - acos(norm_map.z),
	PI / 2 - acos(norm_map.x),
	PI / 2 - acos(norm_map.y)});
	return (norm_obj);
}

__kernel void	render_img(__global t_color *img, __global size_t *p,
				__global t_ray *ray, __global t_intersec *intersec,
				__global uint *n_obj, __global t_obj *obj,
				__global uint *n_light, __global t_light *light,
				__global t_img *textures, __global size_t *j)
{
	t_color	color[3];
	t_ray	vec;
	float3	norm;
	float3	fact[3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
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
	norm = get_norm(textures, &obj[intersec->obj], &vec.pos);
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
		fact[0] = add_vectors(fact[0], mult_vector(((float3){light[i].col.r / (float)255, light[i].col.g / (float)255, light[i].col.b / (float)255}), light[i].i.x * obj[intersec->obj].mat.ref.x));
		if (k == *n_obj)
		{
			fact[1] = add_vectors(fact[1], mult_vector(((float3){light[i].col.r / (float)255, light[i].col.g / (float)255, light[i].col.b / (float)255}), alpha * light[i].i.y * obj[intersec->obj].mat.ref.y * ((scalar_vectors(vec.dir, norm) >= 0) ? scalar_vectors(vec.dir, norm) : 0)));
			vec.dir = sub_vectors(vec.dir, mult_vector(mult_vector(norm, scalar_vectors(vec.dir, norm)), 2));
			normalize_vector(&vec.dir);
			fact[2] = add_vectors(fact[2], mult_vector(((float3){light[i].col.r / (float)255, light[i].col.g / (float)255, light[i].col.b / (float)255}), alpha * (light[i].i.z * obj[intersec->obj].mat.ref.z * pow(scalar_vectors(mult_vector(ray->dir, 0.99), vec.dir), ALPHA))));
		}
		i++;
	}
	fact[0].x = (isnan(fact[0].x)) ? 0 : ((isinf(fact[0].x)) ? 0 : fact[0].x) / 3;
	fact[0].y = (isnan(fact[0].y)) ? 0 : ((isinf(fact[0].y)) ? 0 : fact[0].y) / 3;
	fact[0].z = (isnan(fact[0].z)) ? 0 : ((isinf(fact[0].z)) ? 0 : fact[0].z) / 3;
	fact[1].x = (isnan(fact[1].x)) ? 0 : ((isinf(fact[1].x)) ? 0 : fact[1].x) / 3;
	fact[1].y = (isnan(fact[1].y)) ? 0 : ((isinf(fact[1].y)) ? 0 : fact[1].y) / 3;
	fact[1].z = (isnan(fact[1].z)) ? 0 : ((isinf(fact[1].z)) ? 0 : fact[1].z) / 3;
	fact[2].x = (isnan(fact[2].x)) ? 0 : ((isinf(fact[2].x)) ? 0 : fact[2].x) / 3;
	fact[2].y = (isnan(fact[2].y)) ? 0 : ((isinf(fact[2].y)) ? 0 : fact[2].y) / 3;
	fact[2].z = (isnan(fact[2].z)) ? 0 : ((isinf(fact[2].z)) ? 0 : fact[2].z) / 3;
	color[0] = mult_color(get_color(textures, &obj[intersec->obj], &vec.pos, 0), (1 - obj[intersec->obj].mat.ref.w) * (obj[intersec->obj].mat.col.a / (float)255));
	color[1] = mult_color(get_color(textures, &obj[intersec->obj], &vec.pos, 1), (1 - obj[intersec->obj].mat.ref.w) * (obj[intersec->obj].mat.col.a / (float)255));
	color[2] = mult_color(get_color(textures, &obj[intersec->obj], &vec.pos, 2), (1 - obj[intersec->obj].mat.ref.w) * (obj[intersec->obj].mat.col.a / (float)255));
	color[0].r = (color[0].r * fact[0].x < 0) ? 0 : ((color[0].r * fact[0].x > 255) ? 255 : color[0].r * fact[0].x);
	color[0].g = (color[0].g * fact[0].y < 0) ? 0 : ((color[0].g * fact[0].y > 255) ? 255 : color[0].g * fact[0].y);
	color[0].b = (color[0].b * fact[0].z < 0) ? 0 : ((color[0].b * fact[0].z > 255) ? 255 : color[0].b * fact[0].z);
	color[0].a = 255;

	color[1].r = (color[1].r * fact[1].x < 0) ? 0 : ((color[1].r * fact[1].x > 255) ? 255 : color[1].r * fact[1].x);
	color[1].g = (color[1].g * fact[1].y < 0) ? 0 : ((color[1].g * fact[1].y > 255) ? 255 : color[1].g * fact[1].y);
	color[1].b = (color[1].b * fact[1].z < 0) ? 0 : ((color[1].b * fact[1].z > 255) ? 255 : color[1].b * fact[1].z);
	color[1].a = 255;

	color[2].r = (color[2].r * fact[2].x < 0) ? 0 : ((color[2].r * fact[2].x > 255) ? 255 : color[2].r * fact[2].x);
	color[2].g = (color[2].g * fact[2].y < 0) ? 0 : ((color[2].g * fact[2].y > 255) ? 255 : color[2].g * fact[2].y);
	color[2].b = (color[2].b * fact[2].z < 0) ? 0 : ((color[2].b * fact[0].z > 255) ? 255 : color[2].b * fact[2].z);
	color[2].a = 255;
	*img = add_colors(*img, invert_color(mult_color(add_colors(color[0], add_colors(color[1], color[2])), ray->f)));
}
