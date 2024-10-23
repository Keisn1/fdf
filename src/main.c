#include "fdf.h"
#include "mlx.h"
#include "libft.h"
#include <math.h>
#include <unistd.h>
#include <limits.h>
#include <stdio.h>

int main() {
	void* mlx_ptr = mlx_init();
	if (!mlx_ptr) {
		ft_putendl_fd("Error: Could not establish a connection", STDERR_FILENO);
		return 1;
	}

	void* win_ptr = mlx_new_window(mlx_ptr, 1600 , 900, "first_window");
	if (!win_ptr) {
		ft_putendl_fd("Could not open new window", STDERR_FILENO);
		return 1;
	}

	draw_circ_win(mlx_ptr, win_ptr, (t_circ){100., 0x00ff7f50}, (t_pos){750, 500});

	t_rectangle rect = {600, 500, 0x0000FF00};
	draw_rect_win(mlx_ptr, win_ptr, rect, (t_pos){200, 200});

	/* string handling */
	mlx_string_put(mlx_ptr, win_ptr, 1200, 200, 0x00FFFFFF, "hello Kay");

	/* image handling */
	/* rectangle */
	t_img img_rect = new_img(mlx_ptr, 200, 300);
	fill_img(mlx_ptr, &img_rect, 0x00123456);
	draw_rect_img(mlx_ptr, &img_rect, (t_rectangle){160, 240, 0x000000FF}, (t_pos){20, 30});
	mlx_put_image_to_window(mlx_ptr, win_ptr, img_rect.img, 1100, 500);

	/* circles */
	t_img img_circle = new_img(mlx_ptr, 200, 200);
	fill_img(mlx_ptr, &img_circle, 0x00123456);
	draw_circ_img(mlx_ptr, &img_circle, (t_circ){100, 0x00ff7f50}, (t_pos){100, 100});
	mlx_put_image_to_window(mlx_ptr, win_ptr, img_circle.img, 650, 550);

	t_img img_circle2 = new_img(mlx_ptr, 200, 200);
	fill_img(mlx_ptr, &img_circle2, 0x00654321);
	draw_circ_img(mlx_ptr, &img_circle2, (t_circ){100, 0x00ff7f50}, (t_pos){100, 100});
	mlx_put_image_to_window(mlx_ptr, win_ptr, img_circle2.img, 750, 650);

	/* line */
	t_img img_line = new_img(mlx_ptr, 200, 200);
	fill_img(mlx_ptr, &img_line, 0x000000cd);
	draw_line_img(mlx_ptr, &img_line, (t_line){80, (1./4)*M_PI, 0x00008000}, (t_pos){50, 50});
	mlx_put_image_to_window(mlx_ptr, win_ptr, img_line.img, 200, 650);

	/* triangle */
	double a = 12;
	double b = 14.5;
	double c = 9.8;
	double nbr =  (pow(b, 2) - pow(a, 2) - pow(c, 2) ) /  (2 * a * c);
	double alpha = acos(nbr);
	printf("alpha = %f \n", nbr);
	printf("acos = %f \n", alpha);


	t_img img_triangle = new_img(mlx_ptr, 200, 200);
	fill_img(mlx_ptr, &img_triangle, 0x000000cd);
	draw_line_img(mlx_ptr, &img_triangle, (t_line){c, 0, 0x00008000}, (t_pos){20, 40});
	draw_line_img(mlx_ptr, &img_triangle, (t_line){b, alpha, 0x00008000}, (t_pos){20, 40});
	mlx_put_image_to_window(mlx_ptr, win_ptr, img_triangle.img, 700, 100);


	sleep(3);

	mlx_destroy_image(mlx_ptr, img_rect.img);
	mlx_destroy_image(mlx_ptr, img_circle.img);
	mlx_destroy_image(mlx_ptr, img_circle2.img);
	mlx_destroy_image(mlx_ptr, img_line.img);
	mlx_destroy_image(mlx_ptr, img_triangle.img);

	mlx_destroy_window(mlx_ptr, win_ptr);
	free(mlx_ptr);
    return 0;
}
