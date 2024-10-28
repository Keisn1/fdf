// #include "fdf.h"
// #include "test_fdf.hpp"
// #include "gtest/gtest.h"
// #include <cstddef>
// #include <gtest/gtest.h>
// #include <math.h>

// struct circleTestParam {
// 	t_point mp;
// 	double r;
// 	size_t size;
// };

// class circleTest : public testing::TestWithParam<circleTestParam>{};

// TEST_P(circleTest, circleTest) {
// 	circleTestParam param = GetParam();

// 	t_points circle = new_circle(param.mp, param.r, param.size);
// 	// make sure that the distance is of every point to midpoint is 1
// 	size_t count = 0;

// 	ASSERT_EQ(param.size, circle.length);
// 	while (count < param.size) {
// 		double c_squared = pow(param.mp.x - circle.points[count].x, 2.)  + pow(param.mp.y - circle.points[count].y, 2.);
// 		EXPECT_LT(param.r - sqrt(c_squared), 0.001);
// 		count++;
// 	}
// 	free(circle.points);
// }

// INSTANTIATE_TEST_SUITE_P(
// 	shapeTests,
// 	circleTest,
// 	testing::Values(
// 		circleTestParam{(t_point){2, 2}, 1, 100},
// 		circleTestParam{(t_point){3, 4}, 1, 100}
// 		)
// 	);
