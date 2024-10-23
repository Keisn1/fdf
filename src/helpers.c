#include "fdf.h"
#include "mlx.h"


/* just a thought about UI testing */
/* a test would set up data and checks for right values in data after calling img_put_pixel*/
/* to create my test_data, i would also use mlx_get_color_value */
void img_put_pixel(void *mlx_ptr, t_img *img, t_pos pos, unsigned int color) {
	/* bpp/8 gives you the number of bytes you need to jump, to jump a whole pixel */
	int offset = pos.y * img->size_line + pos.x * (img->bpp/ 8);
	*(unsigned int*)(img->addr + offset) = mlx_get_color_value(mlx_ptr, color);
}

void fill_img(void *mlx_ptr, t_img *img, unsigned int color) {
	/* bpp/8 gives you the number of bytes you need to jump, to jump a whole pixel */
	int x = 0;
	int y = 0;
	while (x < img->width) {
		y =0;
          while (y < img->height)
			  img_put_pixel(mlx_ptr, img, (t_pos){x, y++}, color);
		x++;
	}
}

t_img new_img(void *mlx_ptr, int width, int height) {
	t_img img;
	img.img = mlx_new_image(mlx_ptr, width, height);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.size_line, &img.endian);
	img.width = width;
	img.height = height;
	return img;

}
