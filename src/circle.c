#include "fdf.h"
#include "mlx.h"
#include <math.h>

void draw_circ_win(void* mlx_ptr, void *win_ptr, t_circ circ, t_pos pos) {
	double phi = 0;
	while (phi < 2*M_PI) {
		int y = pos.y + circ.r * cos(phi);
		int x = pos.x + circ.r * sin(phi);
		mlx_pixel_put(mlx_ptr, win_ptr, x, y, circ.color);
		phi += (double)0.01;
	}
}

void draw_circ_img(void *mlx_ptr, t_img *img, t_circ circ, t_pos pos) {
	double phi = 0;
	while (phi < 2*M_PI) {
		int y = pos.y + circ.r * cos(phi);
		int x = pos.x + circ.r * sin(phi);
		img_put_pixel(mlx_ptr, img, (t_pos){x, y}, circ.color);
		phi += (double)0.01;
	}
}

