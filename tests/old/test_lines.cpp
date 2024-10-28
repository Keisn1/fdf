// #include "test_fdf.hpp"
// #include <gtest/gtest.h>

// struct bresenhamTestParams {
//     t_point p_0;
//     t_point p_1;
//     t_points want;
// };

// class bresenhamTest : public testing::TestWithParam<bresenhamTestParams> {};

// TEST_P(bresenhamTest, bresenhamTest) {
//     bresenhamTestParams param = GetParam();

//     t_points got = bres_line(param.p_0, param.p_1);

//     expect_equal_points(param.want, got);

//     free(param.want.points);
//     free(got.points);
// }

// t_points create_want(std::vector<unsigned int> x, std::vector<unsigned int> y) {
//     t_points want = {NULL, x.size()};
//     want.points = (t_point*)malloc(sizeof(t_point) * want.length);
//     if (!want.points) {
//         std::cout << "could not allocate memory for want.points";
//         exit(1);
//     }

//     for (std::size_t i = 0; i < x.size(); ++i) {
//         want.points[i] = (t_point){x[i], y[i]};
//     }
//     return t_points{want.points, x.size()};
// }

// INSTANTIATE_TEST_SUITE_P(
//     bresenhamTests,
//     bresenhamTest,
//     testing::Values(
//         bresenhamTestParams{(t_point){0, 0}, (t_point){0, 0}, create_want({0}, {0})}
//         // bresenhamTestParams{(t_point){0, 0}, (t_point){0, 0}, create_want({0}, {0})}
//         )
//     );
