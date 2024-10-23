#include "fdf.h"
#include <math.h>

void draw_line_img(void *mlx_ptr, t_img *img, t_line line, t_pos pos) {
	double z = 0;
	while (z < line.length) {
		int x = pos.x + cos(line.phi) * z;
		int y = pos.y + sin(line.phi) * z;
		img_put_pixel(mlx_ptr, img, (t_pos){x, y}, line.color);
		z += 0.01;
	}
}
