#include "kernel/kernel.hcl"

__kernel void	colors_efect(__global t_img *img, __global t_color *src, __global int *modi)
{

	/////////////////////////////_realistic efect___/////////////////
	// float r_fact = 0.393;
	// float b_fact = 0.439;
	// float g_fact = 0.400;

	// int		id = get_global_id(0);

	// src[id].r = src[id].r * r_fact;
	// src[id].b = src[id].b * b_fact;
	// src[id].g = src[id].g * g_fact; 
	////////////////////////////////////////__sepia efect________////////////

	int		id = get_global_id(0);


 	/////////////////////NEGATIF//////////////////////////////////////////

//printf("modi %d\n",modi);
	if (*modi == 1)
	{
		float tmp_r = src[id].r;
		float tmp_g = src[id].g;
		float tmp_b = src[id].b;

		src[id].r = 255 - tmp_r;
		src[id].g = 255 - tmp_g;
		src[id].b = 255 - tmp_b;
	}

	////////////////////black and white_binnary//////////////////////////////////////////////
	if (*modi == 2)
	{
		float tmp_r = src[id].b;
	 	float tmp_g = src[id].r;
	 	float tmp_b = src[id].g;
	 	float l = ((0.299 * tmp_r) + (0.587 * tmp_g) + (0.114 * tmp_b));
	 	if (l < 127)
	 	{
	 		src[id].r = 0;
			src[id].b = 0;
			src[id].g = 0;
	 	}
	 	else 
	 	{
	 		src[id].r = 255;
			src[id].b = 255;
			src[id].g = 255;
	 	}
	}

	// niveaux de gris //////////////////////////////////
	if (*modi == 4)
	{
	 	float g = (src[id].b + src[id].r + src[id].g)/3;
		src[id].b = g;
	 	src[id].r = g;
	 	src[id].g = g;

	}
}
