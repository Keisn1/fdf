#include "test_fdf.hpp"
#include "gtest/gtest.h"
#include <gtest/gtest.h>

// setup Mock ////////////////////////////////////////
// Mock class that wraps mlx_pixel_put
class MLXWrapper {
public:
	MOCK_METHOD5(pixelPut, int(void* mlx_ptr, void* win_ptr, int x, int y, int color));
	MOCK_METHOD4(imgPutPixel, void(void* mlx_ptr, t_img *, t_pixel, unsigned int));
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

extern "C" void mock_img_pixel_put(void* mlx_ptr, t_img *img, t_pixel pixel, unsigned int color) {
	if (g_mlxWrapper)
		g_mlxWrapper->imgPutPixel(mlx_ptr, img, pixel, color);
}

MATCHER_P(PixelEq, expected, "") {
    return arg.x == expected.x && arg.y == expected.y;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// bresenhamSimple /////////////////////////////////////////////////////////////////////////////////////////

// struct bresPlotlineSimpleTestParams {
// 	unsigned int x_0;
// 	unsigned int y_0;
// 	unsigned int x_1;
// 	unsigned int y_1;
// 	std::vector<std::vector<unsigned int>> want;
// };

// class bresPlotlineSimpleTest : public testing::TestWithParam<bresPlotlineSimpleTestParams>{};

// TEST_P(bresPlotlineSimpleTest, bresPlotlineSimpleTestParams) {
//     MLXWrapper mock;
// 	g_mlxWrapper = &mock;
// 	bresPlotlineSimpleTestParams params = GetParam();

// 	for (const auto& t: params.want) {
// 		t_pixel px = {t[0], t[1]};
// 		EXPECT_CALL(mock, imgPutPixel(testing::_, testing::_,
// 									  PixelEq(px)
// 								  // testing::Truly([&px](const t_pixel& arg) {return arg.i == px.i && arg.j == px.j;})
// 								  , testing::_));
// 	}

// 	t_line line;
// 	line.pixels[0] = (t_pixel){params.x_0, params.y_0};
// 	line.pixels[1] = (t_pixel){params.x_1, params.y_1};
// 	line.colors[0] = 0;
// 	line.colors[1] = 0;
// 	bres_plotline_simple(t_mlx_data{NULL, NULL, NULL}, NULL, line, mock_img_pixel_put);
// }

// INSTANTIATE_TEST_SUITE_P(
//     bresPlotlineSimpleTest,
// 	bresPlotlineSimpleTest,
// 	testing::Values(
// 		bresPlotlineSimpleTestParams {0, 0, 3, 0, {{0, 0}, {1, 0}, {2, 0}, {3, 0}}},
// 		bresPlotlineSimpleTestParams {0, 0, 3, 3, {{0, 0}, {1, 1}, {2, 2}, {3, 3}}},
// 		bresPlotlineSimpleTestParams {0, 3, 3, 0, {{0, 3} , {1, 2}, {2, 1}, {3, 0}}},
// 		bresPlotlineSimpleTestParams {20, 20, 17, 17, {{20, 20}, {19, 19}, {18, 18}, {17, 17}}},
// 		bresPlotlineSimpleTestParams {0, 3, 0, 0, {{0, 3}, {0, 2}, {0, 1}, {0, 0}}},
// 		bresPlotlineSimpleTestParams {3, 0, 0, 0, {{3, 0}, {2, 0}, {1, 0}, {0, 0}}},
// 		bresPlotlineSimpleTestParams{0, 0, 0, 3, { {0, 0}, {0, 1}, {0, 2}, {0, 3} }},
// 		bresPlotlineSimpleTestParams {17, 20, 20, 17, {{17, 20}, {18, 19}, {19, 18}, {20, 17}}},
// 		bresPlotlineSimpleTestParams {0, 1, 6, 4, {{0, 1}, {1, 1}, {2, 2}, {3, 2}, {4, 3}, {5, 3}, {6, 4}}},
// 		bresPlotlineSimpleTestParams {6, 4, 0, 1, {{6, 4}, {5, 3}, {4, 3}, {3, 2}, {2, 2}, {1, 1}, {0, 1}}},
// 		bresPlotlineSimpleTestParams{0, 3, 0, 0, { {0, 3}, {0, 2}, {0, 1}, {0, 0} }},
// 		bresPlotlineSimpleTestParams {3, 0, 0, 0, {{3, 0}, {2, 0}, {1, 0}, {0, 0}}},
// 		bresPlotlineSimpleTestParams {17, 17, 20, 20, {{17, 17}, {18, 18}, {19, 19}, {20, 20}}},
// 		bresPlotlineSimpleTestParams {17, 17, 20, 20, {{17, 17}, {18, 18}, {19, 19}, {20, 20}}}
// 		)
// 	);

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// bresenhamPlotlineImg /////////////////////////////////////////////////////////////////////////////////////////

struct bresPlotlineImgParams {
	unsigned int x_0;
	unsigned int y_0;
	unsigned int x_1;
	unsigned int y_1;
	std::vector<std::vector<unsigned int>> want;
};

class bresPlotlineImgTest : public testing::TestWithParam<bresPlotlineImgParams>{};

TEST_P(bresPlotlineImgTest, bresPlotlineImgTemplateTest) {
    MLXWrapper mock;
	g_mlxWrapper = &mock;
	bresPlotlineImgParams params = GetParam();

	for (const auto& t: params.want) {
		t_pixel px = {t[0], t[1]};
		EXPECT_CALL(mock, imgPutPixel(testing::_, testing::_,
									  PixelEq(px)
								  // testing::Truly([&px](const t_pixel& arg) {return arg.i == px.i && arg.j == px.j;})
								  , testing::_));
	}

	t_line line;
	line.pixels[0] = (t_pixel){params.x_0, params.y_0};
	line.pixels[1] = (t_pixel){params.x_1, params.y_1};
	line.colors[0] = 0;
	line.colors[1] = 0;
	bres_plotline_img(t_mlx_data{NULL, NULL, NULL}, NULL, line, mock_img_pixel_put);
}

INSTANTIATE_TEST_SUITE_P(
    bresPlotlineImgTemplateTest,
	bresPlotlineImgTest,
	testing::Values(
		bresPlotlineImgParams{0, 0, 0, 3, { {0, 0}, {0, 1}, {0, 2}, {0, 3} }},
		bresPlotlineImgParams {0, 0, 3, 0, {{0, 0}, {1, 0}, {2, 0}, {3, 0}}},
		bresPlotlineImgParams {3, 0, 0, 0, {{3, 0}, {2, 0}, {1, 0}, {0, 0}}},
		bresPlotlineImgParams {0, 3, 0, 0, {{0, 3}, {0, 2}, {0, 1}, {0, 0}}},
		bresPlotlineImgParams {20, 20, 17, 17, {{20, 20}, {19, 19}, {18, 18}, {17, 17}}},
		bresPlotlineImgParams {17, 20, 20, 17, {{17, 20}, {18, 19}, {19, 18}, {20, 17}}},
		bresPlotlineImgParams {0, 1, 6, 4, {{0, 1}, {1, 2}, {2, 2}, {3, 3}, {4, 3}, {5, 4}, {6, 4}}},
		bresPlotlineImgParams {6, 4, 0, 1, {{6, 4}, {5, 3}, {4, 3}, {3, 2}, {2, 2}, {1, 1}, {0, 1}}}
		)
	);


// // breshamLineTest ////////////////////////////////////////
// // testing the function bres_plotline (uses mlx_pixel_put) ////////////////////////////////////////
// struct bresenhamLineTestParams {
// 	unsigned int x_0;
// 	unsigned int y_0;
// 	unsigned int x_1;
// 	unsigned int y_1;
// 	std::vector<std::vector<int>> want;
// };

// class bresenhamPlotLineTest : public testing::TestWithParam<bresenhamLineTestParams>{};

// TEST_P(bresenhamPlotLineTest, BresenhamLineTest) {
//     MLXWrapper mock;
// 	g_mlxWrapper = &mock;
// 	bresenhamLineTestParams params = GetParam();

// 	for (const auto& t: params.want) {
// 		int x = t[0];
// 		int y = t[1];
// 		EXPECT_CALL(mock, pixelPut(testing::_, testing::_, x, y, testing::_
// 						));
// 	}

// 	bres_plotline_window(t_mlx_data{NULL, NULL, NULL},
// 				  (t_pixel){params.x_0, params.y_0},
// 				  (t_pixel){params.x_1, params.y_1},
// 				  mock_pixel_put);
// }

// INSTANTIATE_TEST_SUITE_P(bresenhamTests, bresenhamPlotLineTest,
// 						 testing::Values(
// 							 bresenhamLineTestParams {0, 0, 0, 3, {{0, 0}, {0, 1}, {0, 2}, { 0, 3 }}},
// 							 bresenhamLineTestParams {0, 0, 3, 0, {{0, 0}, {1, 0}, {2, 0}, {3, 0}}},
// 							 bresenhamLineTestParams {3, 0, 0, 0, {{3, 0}, {2, 0}, {1, 0}, {0, 0}}},
// 							 bresenhamLineTestParams {0, 3, 0, 0, {{0, 3}, {0, 2}, {0, 1}, {0, 0}}},
// 							 bresenhamLineTestParams {20, 20, 17, 17, {{20, 20}, {19, 19}, {18, 18}, {17, 17}}},
// 							 bresenhamLineTestParams {17, 20, 20, 17, {{17, 20}, {18, 19}, {19, 18}, {20, 17}}},
// 							 bresenhamLineTestParams {0, 1, 6, 4, {{0, 1}, {1, 2}, {2, 2}, {3, 3}, {4, 3}, {5, 4}, {6, 4}}},
// 							 bresenhamLineTestParams {6, 4, 0, 1, {{6, 4}, {5, 3}, {4, 3}, {3, 2}, {2, 2}, {1, 1}, {0, 1}}}
// 							 )
// 	);

// class bresenhamGetLineTest : public testing::TestWithParam<bresenhamLineTestParams>{};

// TEST_P(bresenhamGetLineTest, BresenhamGetLineTest) {
// 	bresenhamLineTestParams params = GetParam();

// 	t_line line;
// 	line.pixels[0] = {params.x_0, params.y_0};
// 	line.pixels[1] = {params.x_1, params.y_1};
// 	t_list* got = get_bres_line(line);

// 	int count = 0;
// 	t_list *head = got;
// 	while (head) {
// 		t_pixel *p = (t_pixel*)head->content;
// 		EXPECT_EQ(params.want[count][0], p->x);
// 		EXPECT_EQ(params.want[count][1], p->y);
// 		count++;
// 		head = head->next;
// 	}
// 	ft_lstclear(&got, free);
// }

// INSTANTIATE_TEST_SUITE_P(bresenhamGetLineTests, bresenhamGetLineTest,
// 						 testing::Values(
// 							 bresenhamLineTestParams {0, 0, 0, 3, {{0, 0}, {0, 1}, {0, 2}, { 0, 3 }}},
// 							 bresenhamLineTestParams {0, 0, 3, 0, {{0, 0}, {1, 0}, {2, 0}, {3, 0}}},
// 							 bresenhamLineTestParams {3, 0, 0, 0, {{3, 0}, {2, 0}, {1, 0}, {0, 0}}},
// 							 bresenhamLineTestParams {0, 3, 0, 0, {{0, 3}, {0, 2}, {0, 1}, {0, 0}}},
// 							 bresenhamLineTestParams {20, 20, 17, 17, {{20, 20}, {19, 19}, {18, 18}, {17, 17}}},
// 							 bresenhamLineTestParams {17, 20, 20, 17, {{17, 20}, {18, 19}, {19, 18}, {20, 17}}},
// 							 bresenhamLineTestParams {0, 1, 6, 4, {{0, 1}, {1, 2}, {2, 2}, {3, 3}, {4, 3}, {5, 4}, {6, 4}}},
// 							 bresenhamLineTestParams {6, 4, 0, 1, {{6, 4}, {5, 3}, {4, 3}, {3, 2}, {2, 2}, {1, 1}, {0, 1}}}
// 							 )
// 	);


// struct gradientTestParams {
// 	unsigned int col1;
// 	unsigned int col2;
// 	unsigned int steps;
// 	std::vector<unsigned int> want;
// };

// class gradientTest : public ::testing::TestWithParam<gradientTestParams>{};

// TEST_P(gradientTest, gradientTest) {
// 	gradientTestParams params = GetParam();

// 	unsigned int* gradient = get_gradient(params.col1, params.col2, params.steps);
// 	if (params.want.size() == 0) {
// 		ASSERT_EQ(gradient, nullptr);
// 	}
// 	for (size_t i = 0; i < params.want.size(); i++ ) {
// 		EXPECT_EQ(params.want[i], gradient[i]);
// 	}
// 	free(gradient);
// }

// INSTANTIATE_TEST_SUITE_P(gradientTests, gradientTest,
//                          testing::Values(
//                              gradientTestParams{0x0000000, 0x000004, 5, {0, 1, 2, 3, 4}},
//                              gradientTestParams{0x001F00, 0x001F00, 5, {0, 1, 2, 3, 4}}
// 							 )
// 	);
