#include "kernel/kernel.hcl"

__kernel void	colors_efect(__global t_img *img, __global t_color *src, __global int *modi)
{

	int		id = get_global_id(0);
	if (*modi == 1) //NEGATIF
	{
		float tmp_r = src[id].r;
		float tmp_g = src[id].g;
		float tmp_b = src[id].b;

		src[id].r = 255 - tmp_r;
		src[id].g = 255 - tmp_g;
		src[id].b = 255 - tmp_b;
	}
	else if (*modi == 2)// niveaux de gris
	{
	 	float g = (src[id].b + src[id].r + src[id].g)/3;
		src[id].b = g;
	 	src[id].r = g;
	 	src[id].g = g;

	}
	else if (*modi == 3) //sepia
	{

		float tmp_r = src[id].r;
		float tmp_g = src[id].g;
		float tmp_b = src[id].b;


		if ((tmp_b * 0.393) + (tmp_g * 0.769) + (tmp_r * 0.189) > 255)
			src[id].b = 255;
		else
			src[id].b = (int)((tmp_b * 0.393) + (tmp_g * 0.769) + (tmp_r * 0.189));

		if ((tmp_b * 0.349) + (tmp_g * 0.686) + (tmp_r * 0.168) > 255)
			src[id].g = 255;
		else
			src[id].g = (int)((tmp_b * 0.349) + (tmp_g * 0.686) + (tmp_r * 0.168));

		if ((tmp_b * 0.272) + (tmp_g * 0.534) + (tmp_r * 0.131) > 255)
			src[id].r = 255;
		else
			src[id].r = (int)((tmp_b * 0.272) + (tmp_g * 0.534) + (tmp_r * 0.131)) ;

	}
}