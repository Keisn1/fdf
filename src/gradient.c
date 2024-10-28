#include "fdf.h"
#include <unistd.h>

/* unsigned int *get_grad(int pixels) { */
/* 	unsigned int *grad = (unsigned int*)malloc(sizeof(unsigned int) * pixels); */
/* 	if (!grad) */
/* 		return NULL; */
/* 	int pixel = 0; */
/* 	/\* 12 color apartements, changing a value from 0 to 128 *\/ */
/* 	int col_step = (pixels/12); */
/* 	int pixel_step = 128 / col_step; */
/* 	/\* one actually need to decide for a direction *\/ */
/* 	/\* red to rose *\/ */
/* 	unsigned int red = 255; */
/* 	unsigned int blue = 0; */
/* 	unsigned int green = 0; */
/* 	while (pixel < col_step) { */
/* 		grad[pixel] = create_rgb(red, green, blue); */
/* 		blue += pixel_step; */
/* 		pixel++; */
/* 	} */
/* 	col_step += col_step; */

/* 	/\* rose to magenta *\/ */
/* 	blue = 128; */
/* 	while (pixel < col_step) { */
/* 		grad[pixel] = create_rgb(red, green, blue); */
/* 		blue += pixel_step; */
/* 		pixel++; */
/* 	} */
/* 	col_step += col_step; */

/* 	/\* magenta to violet *\/ */
/* 	while (pixel < col_step) { */
/* 		grad[pixel] = create_rgb(red, green, blue); */
/* 		red -= pixel_step; */
/* 		pixel++; */
/* 	} */
/* 	col_step += col_step; */

/* 	/\* violet to blue *\/ */
/* 	red = 128; */
/* 	while (pixel < col_step) { */
/* 		grad[pixel] = create_rgb(red, green, blue); */
/* 		red -= pixel_step; */
/* 		pixel++; */
/* 	} */
/* 	col_step += col_step; */

/* 	/\* blue to azure *\/ */
/* 	red = 0; */
/* 	while (pixel < col_step) { */
/* 		grad[pixel] = create_rgb(red, green, blue); */
/* 		green += pixel_step; */
/* 		pixel++; */
/* 	} */
/* 	col_step += col_step; */
/* 	/\* azure to cyan *\/ */
/* 	green = 128; */
/* 	while (pixel < col_step) { */
/* 		grad[pixel] = create_rgb(red, green, blue); */
/* 		green += pixel_step; */
/* 		pixel++; */
/* 	} */
/* 	col_step += col_step; */
/* 	/\* cyan to spring green *\/ */
/* 	/\* spring green to green *\/ */

/* 	/\* green to chartreuse *\/ */
/* 	/\* chartreuse to yellow *\/ */
/* 	/\* yellow to orange *\/ */
/* 	/\* orange to red *\/ */

/* 	return grad; */
/* } */
