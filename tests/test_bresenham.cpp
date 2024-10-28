#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "fdf.h"

// Mock class that wraps mlx_pixel_put
class MLXWrapper {
public:
    MOCK_METHOD5(pixelPut, int(void* mlx_ptr, void* win_ptr, int x, int y, int color));
};

// Global or static instance for the test
MLXWrapper* g_mlxWrapper = nullptr;

// Replace with the mocked version
extern "C" int mlx_pixel_put(void* mlx_ptr, void* win_ptr, int x, int y, int color) {
    if (g_mlxWrapper) {
        return g_mlxWrapper->pixelPut(mlx_ptr, win_ptr, x, y, color);
    }
    return 0;
}

// Wrap your draw_rect_win call to use g_mlxWrapper
void draw_rect_win(void* mlx_ptr, void* win_ptr, int p1, int p2, MLXWrapper& mlxWrapper) {
    g_mlxWrapper = &mlxWrapper;
    int x = p1;
    int y = p2;
    while (x < 100) {
        y = p2;
        while (y < 200) {
            mlx_pixel_put(mlx_ptr, win_ptr, x, y++, 0xFF00FF);
        }
        x++;
    }
    g_mlxWrapper = nullptr;
}

// Example test
TEST(DrawRectWinTest, CallsMlxPixelPutCorrectly) {
    MLXWrapper mock;
    const int start_x = 10;
    const int start_y = 20;

    // Expect mlx_pixel_put to be called 90 * 180 times with specific parameters
    EXPECT_CALL(mock, pixelPut(testing::_, testing::_, testing::AllOf(testing::Ge(0), testing::Le(100)),  testing::Lt(200), 0xFF00FF))
        .Times((100 - start_x) * (200 - start_y));

    draw_rect_win(nullptr, nullptr, start_x, start_y, mock);
}


//////////////////////////////////////////////////////////////////////
// old stuff

// struct bresenhamTestParams {
//     t_point p_0;
//     t_point p_1;
//     t_points want;
// };

// class bresenhamTest : public testing::TestWithParam<bresenhamTestParams> {};

// TEST_P(bresenhamTest, bresenhamTest) {
// 	bresenhamTestParams param = GetParam();

// 	t_points got = bres_line(param.p_0, param.p_1);

// 	expect_equal_points(param.want, got);

// 	free(param.want.points);
// 	free(got.points);
// }

// t_points create_want(std::vector<int> x, std::vector<int> y) {
// 	t_points want = {NULL, x.size()};
// 	want.points = (t_point*)malloc(sizeof(t_point) * want.length);
// 	if (!want.points) {
// 		std::cout << "could not allocate memory for want.points";
// 		exit(1);
// 	}

//     for (std::size_t i = 0; i < x.size(); ++i) {
// 		want.points[i] = (t_point){x[i], y[i]};
// 	}
// 	return t_points{want.points, x.size()};
// }

// INSTANTIATE_TEST_SUITE_P(
//     bresenhamTests,
// 	bresenhamTest,
// 	testing::Values(
// 		bresenhamTestParams{(t_point){0, 0}, (t_point){0, 0}, create_want({0}, {0})},
// 		bresenhamTestParams{(t_point){0, 0}, (t_point){0, 2}, create_want({0, 0, 0}, {0, 1, 2})}
// 		)
// 	);
