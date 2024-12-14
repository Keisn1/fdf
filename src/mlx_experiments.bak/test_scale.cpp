// #include "test_scale.h"


// TEST(scaleTest, scaleTest) {
// 	t_extrema limits = {-23.3, -33.5, 44.5, 22.5};
// 	unsigned int size_x = 1920;
// 	unsigned int size_y = 1080;

// 	unsigned int scale = get_scale(size_x, size_y, limits);

// 	EXPECT_EQ( 32, scale);		// 1080 / 33.5 = 32 is the lowest

// 	limits = {-89.3, -21.5, 44.5, 22.5};
// 	scale = get_scale(size_x, size_y, limits);
// 	EXPECT_EQ( 21, scale);

// 	limits = {-21.5, -89.3, 44.5, 22.5};
// 	scale = get_scale(size_x, size_y, limits);
// 	EXPECT_EQ( 12, scale);

// 	limits = {-21.5,  44.5,-89.3, 22.5};
// 	scale = get_scale(size_x, size_y, limits);
// 	EXPECT_EQ( 21, scale);

// 	limits = {-21.5,  44.5, 22.5, -89.3};
// 	scale = get_scale(size_x, size_y, limits);
// 	EXPECT_EQ( 12, scale);
// }
