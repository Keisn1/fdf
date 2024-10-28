#include "fdf.h"
#include <math.h>


/* void draw_triangle_img(void *mlx_ptr, t_img *img, t_triangle t, t_point pos) { */
/* 	draw_line_img(mlx_ptr, img, (t_line){t.c, 0, 0x00008000}, pos); */
/* 	draw_line_img(mlx_ptr, img, (t_line){t.b, t.alpha, 0x00008000}, pos); */
/* 	draw_line_img(mlx_ptr, img, (t_line){t.a, M_PI - t.beta, 0x00008000}, (t_point){pos.x + t.c, pos.y}); */
/* } */

/* t_triangle new_triangle(double a, double b, double c) { */
/* 	t_triangle triangle; */
/* 	triangle.alpha =  acos((pow(b, 2) + pow(c, 2) - pow(a, 2) ) /  (2 * b * c)); */
/* 	triangle.beta =  acos((pow(c, 2) + pow(a, 2) - pow(b, 2) ) /  (2 * a * c)); */
/* 	triangle.gamma =  acos((pow(a, 2) + pow(b, 2) - pow(c, 2) ) /  (2 * a * b)); */
/* 	triangle.a = a; */
/* 	triangle.b = b; */
/* 	triangle.c = c; */
/* 	return triangle; */
/* } */
