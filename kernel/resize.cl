typedef struct	s_color
{
	uchar		r;
	uchar		g;
	uchar		b;
	uchar		a;
}				t_color;

typedef struct	s_img
{
	void		*ptr;
	t_color		*img;
	int			w;
	int			h;
}				t_img;

__kernel void	resize(__global t_img *img_dest, __global t_color *dest,
						__global t_img *img_src, __global t_color *src)
{
	int		id = get_global_id(0);
	int		x = id % img_dest->w;
	int		y = id / img_dest->w;

	dest[y * img_dest->w + x] = src[(int)((int)(y * img_src->h / (float)img_dest->h) * img_src->w + x * img_src->w / (float)img_dest->w)];
}