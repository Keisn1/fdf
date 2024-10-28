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

// C-style function matching the PixelPutFunc signature
extern "C" int mock_pixel_put(void* mlx_ptr, void* win_ptr, int x, int y, int color) {
	if (g_mlxWrapper) {
		return g_mlxWrapper->pixelPut(mlx_ptr, win_ptr, x, y, color);
	}
	return 0;
}

struct bresenhamLineTestParams {
	int x_0;
	int y_0;
	int x_1;
	int y_1;
	std::vector<std::tuple<int, int>> want;
};

class BresenhamLineTest : public testing::TestWithParam<bresenhamLineTestParams>{};

TEST_P(BresenhamLineTest, BresenhamLineTest) {
    MLXWrapper mock;
	g_mlxWrapper = &mock;
	bresenhamLineTestParams params = GetParam();

	for (const auto& t: params.want) {
		int x, y;
		std::tie(x, y) = t;
		EXPECT_CALL(mock, pixelPut(testing::_, testing::_, x, y, testing::_
						));
	}

	bres_plotline(t_mlx_data{NULL, NULL},
				  (t_point){params.x_0, params.y_0},
				  (t_point){params.x_1, params.y_1},
				  mock_pixel_put);
}

INSTANTIATE_TEST_SUITE_P(bresenhamTests, BresenhamLineTest,
						 testing::Values(
							 bresenhamLineTestParams {0, 0, 0, 3, {{0, 0}, {0, 1}, {0, 2}, { 0, 3 }}},
							 bresenhamLineTestParams {0, 0, 3, 0, {{0, 0}, {1, 0}, {2, 0}, {3, 0}}},
							 bresenhamLineTestParams {3, 0, 0, 0, {{3, 0}, {2, 0}, {1, 0}, {0, 0}}},
							 bresenhamLineTestParams {0, 3, 0, 0, {{0, 3}, {0, 2}, {0, 1}, {0, 0}}},
							 bresenhamLineTestParams {20, 20, 17, 17, {{20, 20}, {19, 19}, {18, 18}, {17, 17}}},
							 bresenhamLineTestParams {17, 20, 20, 17, {{17, 20}, {18, 19}, {19, 18}, {20, 17}}},
							 bresenhamLineTestParams {0, 1, 6, 4, {{0, 1}, {1, 2}, {2, 2}, {3, 3}, {4, 3}, {5, 4}, {6, 4}}},
							 bresenhamLineTestParams {6, 4, 0, 1, {{6, 4}, {5, 3}, {4, 3}, {3, 2}, {2, 2}, {1, 1}, {0, 1}}}
							 )
	);
