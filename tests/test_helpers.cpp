#include "test_fdf.hpp"


void expect_equal_points(t_points want, t_points got) {
	EXPECT_EQ(want.length, got.length);
	size_t count = 0;
	while (count < want.length) {
		EXPECT_EQ(want.points[count].x, got.points[count].x);
		EXPECT_EQ(want.points[count].y, got.points[count].y);
		count++;
	}
}
