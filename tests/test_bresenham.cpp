#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "fdf.h"
#include "libft.h"

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
	unsigned int x_0;
	unsigned int y_0;
	unsigned int x_1;
	unsigned int y_1;
	std::vector<std::vector<int>> want;
};

class bresenhamPlotLineTest : public testing::TestWithParam<bresenhamLineTestParams>{};

TEST_P(bresenhamPlotLineTest, BresenhamLineTest) {
    MLXWrapper mock;
	g_mlxWrapper = &mock;
	bresenhamLineTestParams params = GetParam();

	for (const auto& t: params.want) {
		int x = t[0];
		int y = t[1];
		EXPECT_CALL(mock, pixelPut(testing::_, testing::_, x, y, testing::_
						));
	}

	bres_plotline(t_mlx_data{NULL, NULL},
				  (t_point){params.x_0, params.y_0},
				  (t_point){params.x_1, params.y_1},
				  mock_pixel_put);
}

INSTANTIATE_TEST_SUITE_P(bresenhamTests, bresenhamPlotLineTest,
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

class bresenhamGetLineTest : public testing::TestWithParam<bresenhamLineTestParams>{};

TEST_P(bresenhamGetLineTest, BresenhamGetLineTest) {
	bresenhamLineTestParams params = GetParam();

	t_point p_0 = {params.x_0, params.y_0};
	t_point p_1 = {params.x_1, params.y_1};
	t_list* got = get_bres_line(p_0, p_1);

	int count = 0;
	t_list *head = got;
	while (head) {
		t_point *p = (t_point*)head->content;
		EXPECT_EQ(params.want[count][0], p->x);
		EXPECT_EQ(params.want[count][1], p->y);
		count++;
		head = head->next;
	}
	ft_lstclear(&got, free);
}

INSTANTIATE_TEST_SUITE_P(bresenhamGetLineTests, bresenhamGetLineTest,
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
