#include "fdf.h"
#include "mlx.h"
#include <stdlib.h>

/* /\* just a thought about UI testing *\/ */
/* /\* a test would set up data and checks for right values in data after calling img_put_pixel*\/ */
/* /\* to create my test_data, i would also use mlx_get_color_value *\/ */
void img_put_pixel(void *mlx_ptr, t_img *img, t_point pos, unsigned int color) {
	/* bpp/8 gives you the number of bytes you need to jump, to jump a whole pixel */
	int offset = pos.j * img->size_line + pos.i * (img->bpp/ 8);
	*(unsigned int*)(img->img_pixels + offset) = mlx_get_color_value(mlx_ptr, color);
}

/* void fill_img(void *mlx_ptr, t_img *img, unsigned int color) { */
/* 	/\* bpp/8 gives you the number of bytes you need to jump, to jump a whole pixel *\/ */
/* 	int x = 0; */
/* 	int y = 0; */
/* 	while (x < img->width) { */
/* 		y =0; */
/*           while (y < img->height) */
/* 			  img_put_pixel(mlx_ptr, img, (t_point){x, y++}, color); */
/* 		x++; */
/* 	} */
/* } */

t_img new_img(void *mlx_ptr, int width, int height) {
	t_img img;
	img.img = mlx_new_image(mlx_ptr, width, height);
	img.img_pixels = mlx_get_data_addr(img.img, &img.bpp, &img.size_line, &img.endian);
	img.width = width;
	img.height = height;
	return img;
}

/* int	create_rgb( int r, int g, int b) */
/* { */
/* 	return (r << 16 | g << 8 | b); */
/* } */


int my_mlx_pixel_put(void *mlx_ptr, void *win_ptr, int x, int y, int color) {
	return mlx_pixel_put(mlx_ptr, win_ptr, x, y, color);
}

void free_matrix(t_mat M) {
	int m_count = 0;
	while (m_count < M.m) {
		free(M.mat[m_count]);
		m_count++;
	}
	free(M.mat);
}
