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

__kernel void	antialiasing(__global t_img *size, __global t_color *dest, __global t_color *src)
{
	t_color	color;
	uint	r;
	uint	g;
	uint	b;
	uint	a;
	int		id = get_global_id(0);
	int		x = id % size->w;
	int		y = id / size->w;
	uchar	n;

	n = 1;
	color = src[id];
	r = color.r;
	g = color.g;
	b = color.b;
	a = color.a;
	if (x)
	{
		n++;
		color = src[y * size->w + x - 1];
		r += color.r;
		g += color.g;
		b += color.b;
		a += color.a;
		if (y)
		{
			n++;
			color = src[(y - 1) * size->w + x - 1];
			r += color.r;
			g += color.g;
			b += color.b;
			a += color.a;
		}
		if (y < size->h - 1)
		{
			n++;
			color = src[(y + 1) * size->w + x - 1];
			r += color.r;
			g += color.g;
			b += color.b;
			a += color.a;
		}
	}
	if (x < size->w - 1)
	{
		n++;
		color = src[y * size->w + x + 1];
		r += color.r;
		g += color.g;
		b += color.b;
		a += color.a;
		if (y)
		{
			n++;
			color = src[(y - 1) * size->w + x + 1];
			r += color.r;
			g += color.g;
			b += color.b;
			a += color.a;
		}
		if (y < size->h - 1)
		{
			n++;
			color = src[(y + 1) * size->w + x + 1];
			r += color.r;
			g += color.g;
			b += color.b;
			a += color.a;
		}
	}
	if (y)
	{
		n++;
		color = src[(y - 1) * size->w + x];
		r += color.r;
		g += color.g;
		b += color.b;
		a += color.a;
	}
	if (y < size->h - 1)
	{
		n++;
		color = src[(y + 1) * size->w + x];
		r += color.r;
		g += color.g;
		b += color.b;
		a += color.a;
	}
	dest[id].r = r / n;
	dest[id].g = g / n;
	dest[id].b = b / n;
	dest[id].a = a / n;
}