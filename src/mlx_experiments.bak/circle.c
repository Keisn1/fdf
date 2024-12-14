#include "fdf.h"
#include "libft.h"
#include "mlx.h"
#include <math.h>

/* void draw_circ_win(t_mlx_data mlx_data, t_circ circ, t_point mid_point) { */
/* 	double phi = 0; */
/* 	while (phi < 2*M_PI) { */
/* 		int y = mid_point.y + circ.r * sin(phi); */
/* 		int x = mid_point.x + circ.r * cos(phi); */
/* 		mlx_pixel_put(mlx_data.mlx_ptr, mlx_data.win_ptr, x, y, circ.color); */
/* 		phi += (double)0.01; */
/* 	} */
/* } */

/* void draw_circ_img(void *mlx_ptr, t_img *img, t_circ circ, t_point pos) { */
/* 	double phi = 0; */
/* 	while (phi < 2*M_PI) { */
/* 		int y = pos.y + circ.r * cos(phi); */
/* 		int x = pos.x + circ.r * sin(phi); */
/* 		img_put_pixel(mlx_ptr, img, (t_point){x, y}, circ.color); */
/* 		phi += (double)0.01; */
/* 	} */
/* } */

/* t_points new_circle(t_point mp, double r, size_t size) { */
/* 	if (mp.x) { */
/* 		if (r) { */
/* 		} */
/* 	} */
/* 	t_point* points = (t_point*)malloc(sizeof(t_point) * size); */
/* 	if (!points) { */
/* 		return (t_points){NULL, 0}; */
/* 	} */

/* 	size_t count = 0; */
/* 	double step = 2*M_PI / (double)size; */
/* 	double phi = 0; */
/* 	while (count < size) { */
/* 		double x = mp.x + r * cos(phi); */
/* 		double y = mp.y + r * sin(phi); */
/* 		points[count++] = (t_point){x, y}; */
/* 		phi += step; */
/* 	} */
/* 	return (t_points){points, size}; */
/* } */
