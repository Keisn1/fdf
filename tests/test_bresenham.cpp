#include "test_fdf.hpp"

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
    return arg.i == expected.i && arg.j == expected.j;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// bresenhamTemplateTest /////////////////////////////////////////////////////////////////////////////////////////
// testing the function bresenham_template ///////////////////////////////////////////////////////////////////////
// without dependency injection and dedicated mock function inside source ////////////////////////////////////////

struct bresPlotlineImgTemplateTestParams {
	unsigned int x_0;
	unsigned int y_0;
	unsigned int x_1;
	unsigned int y_1;
	std::vector<std::vector<unsigned int>> want;
};

class bresPlotlineImgTemplateTest : public testing::TestWithParam<bresPlotlineImgTemplateTestParams>{};

TEST_P(bresPlotlineImgTemplateTest, bresPlotlineImgTemplateTest) {
    MLXWrapper mock;
	g_mlxWrapper = &mock;
	bresPlotlineImgTemplateTestParams params = GetParam();

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
	bresPlotlineImgTemplateTest,
	testing::Values(
		bresPlotlineImgTemplateTestParams{0, 0, 0, 3, { {0, 0}, {0, 1}, {0, 2}, {0, 3} }},
		bresPlotlineImgTemplateTestParams {0, 0, 3, 0, {{0, 0}, {1, 0}, {2, 0}, {3, 0}}},
		bresPlotlineImgTemplateTestParams {3, 0, 0, 0, {{3, 0}, {2, 0}, {1, 0}, {0, 0}}},
		bresPlotlineImgTemplateTestParams {0, 3, 0, 0, {{0, 3}, {0, 2}, {0, 1}, {0, 0}}},
		bresPlotlineImgTemplateTestParams {20, 20, 17, 17, {{20, 20}, {19, 19}, {18, 18}, {17, 17}}},
		bresPlotlineImgTemplateTestParams {17, 20, 20, 17, {{17, 20}, {18, 19}, {19, 18}, {20, 17}}},
		bresPlotlineImgTemplateTestParams {0, 1, 6, 4, {{0, 1}, {1, 2}, {2, 2}, {3, 3}, {4, 3}, {5, 4}, {6, 4}}},
		bresPlotlineImgTemplateTestParams {6, 4, 0, 1, {{6, 4}, {5, 3}, {4, 3}, {3, 2}, {2, 2}, {1, 1}, {0, 1}}}
		)
	);


// breshamLineTest ////////////////////////////////////////
// testing the function bres_plotline (uses mlx_pixel_put) ////////////////////////////////////////
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

	bres_plotline_window(t_mlx_data{NULL, NULL, NULL},
				  (t_pixel){params.x_0, params.y_0},
				  (t_pixel){params.x_1, params.y_1},
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

	t_pixel p_0 = {params.x_0, params.y_0};
	t_pixel p_1 = {params.x_1, params.y_1};
	t_list* got = get_bres_line(p_0, p_1);

	int count = 0;
	t_list *head = got;
	while (head) {
		t_pixel *p = (t_pixel*)head->content;
		EXPECT_EQ(params.want[count][0], p->i);
		EXPECT_EQ(params.want[count][1], p->j);
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
