#include "test_fdf.hpp"

struct minMaxTestParams {
	std::vector<std::vector<double>> M;
	double want_min_x;
	double want_min_y;
	double want_max_x;
	double want_max_y;
};

class minMaxTest : public testing::TestWithParam<minMaxTestParams>{};

TEST_P(minMaxTest, minMaxTest) {
	minMaxTestParams params = GetParam();
	double** matrix = create_matrix(params.M);
	t_matrix M = {matrix, 0, 0};

	if (params.M.size() > 0) {
		M.m = params.M.size();
		M.n = params.M[0].size();
	}

	t_extrema limits_M =	get_extrema(M);

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

