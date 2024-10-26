#include "fdf.h"
#include "mlx.h"
#include <gtest/gtest.h>

// void free_cart(unsigned int **cart, size_t size) {
// 	size_t count = 0;
// 	while (count < size)
// 		free(cart[count++]);
// 	free(cart);
// }

// TEST(lineTestSuite, bresenham) {
// 	size_t x = 20;
// 	size_t y = 20;
// 	unsigned int **cart = (unsigned int**)malloc(sizeof(unsigned int*)  * y);
// 	if (!cart) {
// 		FAIL();
// 		exit(0);
// 	}
// 	size_t count = 0;
// 	while (count < x) {
// 		cart[count] = (unsigned int*)malloc(sizeof(unsigned int));
// 		if (!cart[count]) {
// 			free_cart(cart, count);
// 			FAIL();
// 			exit(0);
// 		}
// 		count++;
// 	}
// 	free_cart(cart, count);
// }
