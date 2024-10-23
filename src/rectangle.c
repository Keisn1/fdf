#include "fdf.h"
#include "mlx.h"

void draw_rect_win(void* mlx_ptr, void *win_ptr, t_rectangle rect, t_pos pos) {
	int x = pos.x;
	int y = pos.y;
	while (x < rect.width) {
		y = pos.y;
		while (y < rect.height)
			mlx_pixel_put(mlx_ptr, win_ptr, x, y++, rect.color);
		x++;
	}
}

void draw_rect_img(void *mlx_ptr, t_img *img, t_rectangle rect, t_pos pos) {
	int x = pos.x;
	while (x < rect.width) {
		int y = pos.y;
		while (y < rect.height) {
			img_put_pixel(mlx_ptr, img, (t_pos){x, y}, rect.color);
			y++;
		}
		x++;
	}
}
