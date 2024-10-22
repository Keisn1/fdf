#include "mlx.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>

void printBinary(unsigned int num) {
    // Assuming a 32-bit integer for demonstration
    for (int i = sizeof(num) * 8 - 1; i >= 0; i--) {
        unsigned int mask = 1 << i;
        printf("%d", (num & mask) ? 1 : 0);
    }
    printf("\n");
}

int rgb(int red, int green, int blue) {
	int color = red << 16;
	color += (green<<8);
	color += blue;
	return color;
}


int main() {
	void* mlx_ptr = mlx_init();
	if (!mlx_ptr) {
		printf("Could not establish connection");
		return 1;
	}

	void* win_ptr = mlx_new_window(mlx_ptr, 1600 , 900, "first_window");
	if (!win_ptr) {
		printf("Could not open new window");
		return 1;
	}

	/* putting a lane */
	int count1 = 0;
	while (count1++ < 900) {
		int count2 = 200;
		while (count2++ < 400) {
			mlx_pixel_put( mlx_ptr, win_ptr, count2, count1, rgb(255, 255, 255));
		}
	}
	/* putting string */
	mlx_string_put(mlx_ptr, win_ptr, 1200, 450, rgb(255, 255, 255), "hello Kay");

	sleep(3);
	mlx_destroy_window(mlx_ptr, win_ptr);
	free(mlx_ptr);
    return 0;
}
