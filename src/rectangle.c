/* #include "fdf.h" */
/* #include "mlx.h" */

/* void draw_rect_win(t_mlx_data mlx_data, t_rectangle rect, t_point pos) { */
/* 	int x = pos.x; */
/* 	int y = pos.y; */
/* 	while (x < rect.width) { */
/* 		y = pos.y; */
/* 		while (y < rect.height) */
/* 			mlx_pixel_put(mlx_data.mlx_ptr, mlx_data.win_ptr, x, y++, rect.color); */
/* 		x++; */
/* 	} */
/* } */

/* void draw_rect_img(void *mlx_ptr, t_img *img, t_rectangle rect, t_point pos) { */
/* 	int x = pos.x; */
/* 	while (x < rect.width) { */
/* 		int y = pos.y; */
/* 		while (y < rect.height) { */
/* 			img_put_pixel(mlx_ptr, img, (t_point){x, y}, rect.color); */
/* 			y++; */
/* 		} */
/* 		x++; */
/* 	} */
/* } */


/* void draw_rect_win(void* mlx_ptr, void* win_ptr, int p1, int p2, PixelPutFunc pixel_put) { */
/*     int x = p1; */
/*     int y = p2; */
/*     while (x < 100) { */
/*         y = p2; */
/*         while (y < 200) { */
/*             pixel_put(mlx_ptr, win_ptr, x, y++, 0xFF00FF); */
/*         } */
/*         x++; */
/*     } */
/* } */
