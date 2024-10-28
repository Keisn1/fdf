#include "fdf.h"
#include "libft.h"
#include <stdlib.h>
#include "mlx.h"


void test_fun(void *mlx_ptr, void *win_ptr, int x, int y) {
	my_mlx_pixel_put(mlx_ptr,  win_ptr, x, y, 0xFF00FF);
}

t_points bres_line(t_point p_0, t_point p_1) {
	if (p_1.x) {
	}
	t_point* points = (t_point*)malloc(sizeof(t_point) * 2);
	if (!points)
		return (t_points){NULL, 0};

	points[0] = p_0;

	return (t_points){points, 1};
}

void plotLine(int x0, int y0, int x1, int y1)
{
	int dx =  abs(x1-x0), sx = x0<x1 ? 1 : -1;
	int dy = -abs(y1-y0), sy = y0<y1 ? 1 : -1;
	int err = dx+dy, e2;                                  /* error value e_xy */

	for (;;) {                                                        /* loop */
/* setPixel(x0,y0); */
/* to test this function we would need to stub it or mock it (good case actually) */
		e2 = 2*err;
		if (e2 >= dy) {                                       /* e_xy+e_x > 0 */
			if (x0 == x1) break;
			err += dy; x0 += sx;
		}
		if (e2 <= dx) {                                       /* e_xy+e_y < 0 */
			if (y0 == y1) break;
			err += dx; y0 += sy;
		}
	}
}
