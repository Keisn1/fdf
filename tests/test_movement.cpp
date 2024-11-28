#include "test_fdf.hpp"

TEST(scaleTest, scaleTest) {
	t_limits limits = {-23.3, -33.5, 44.5, 22.5};
	unsigned int size_x = 1920;
	unsigned int size_y = 1080;

	unsigned int scale = get_scale(size_x, size_y, limits);

	EXPECT_EQ( 32, scale);		// 1080 / 33.5 = 32 is the lowest

	limits = {-89.3, -21.5, 44.5, 22.5};
	scale = get_scale(size_x, size_y, limits);
	EXPECT_EQ( 21, scale);

	limits = {-21.5, -89.3, 44.5, 22.5};
	scale = get_scale(size_x, size_y, limits);
	EXPECT_EQ( 12, scale);

	limits = {-21.5,  44.5,-89.3, 22.5};
	scale = get_scale(size_x, size_y, limits);
	EXPECT_EQ( 21, scale);

	limits = {-21.5,  44.5, 22.5, -89.3};
	scale = get_scale(size_x, size_y, limits);
	EXPECT_EQ( 12, scale);
}


struct minMaxTestParams {
	std::vector<std::vector<double>> M;
	double want_min_x;
	double want_min_y;
	double want_max_x;
	double want_max_y;
};

class minMaxTest : public testing::TestWithParam<minMaxTestParams>{};

INSTANTIATE_TEST_SUITE_P(scaleTest, minMaxTest,
                         testing::Values(
							 minMaxTestParams{{}, 0, 0,0, 0},
							 minMaxTestParams{{{1}, {1}}, 1, 1, 1, 1},
							 minMaxTestParams{{{1}, {-1}}, 1, -1, 1, -1},
							 minMaxTestParams{{{1}, {-1.2}}, 1, -1.2, 1, -1.2},
							 minMaxTestParams{{{1, -1.2}, {4.7, -3.6}}, -1.2, -3.6, 1,4.7},
							 minMaxTestParams{{{1, -1.2, 3.2, -0.2, -4.5}, {4.7, -3.6, 2.2, -10.1, 5.3}}, -4.5, -10.1, 3.2,5.3}
                             )
	);


TEST_P(minMaxTest, minMaxTest) {
	minMaxTestParams params = GetParam();
	double** matrix = create_matrix(params.M);
	t_mat M = {matrix, 0, 0};

	if (params.M.size() > 0) {
		M.m = params.M.size();
		M.n = params.M[0].size();
	}

	t_limits limits_M =	get_limits(M);

	EXPECT_EQ(params.want_min_x, limits_M.min_x);
	EXPECT_EQ(params.want_min_y, limits_M.min_y);
	EXPECT_EQ(params.want_max_x, limits_M.max_x);
	EXPECT_EQ(params.want_max_y, limits_M.max_y);
	if (params.M.size() > 0) {
		free(M.mat[0]);
		free(M.mat[1]);
		free(M.mat);
	}

}
