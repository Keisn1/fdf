#include "test_fdf.hpp"

struct MatMulTestParam {
	std::vector<std::vector<double>> X;
	std::vector<std::vector<double>> Y;
	std::vector<std::vector<double>> want;
};

class MatMulTest : public testing::TestWithParam<MatMulTestParam> {};



TEST_P(MatMulTest, MatMulTest) {
	MatMulTestParam params = GetParam();
	t_matrix X = new_matrix(params.X);
	t_matrix Y = new_matrix(params.Y);
	t_matrix want = new_matrix(params.want);

	t_matrix got = mat_mul(X, Y);

	EXPECT_EQ(want.m, got.m);
	EXPECT_EQ(want.n, got.n);
	for (unsigned int i = 0; i < want.m ; i++) {
		for (unsigned int j = 0; j < want.n ; j++) {
			EXPECT_EQ(want.mat[i][j], got.mat[i][j]);
		}
	}

	free_matrix(X);
	free_matrix(Y);
	free_matrix(want);
	free_matrix(got);
}

INSTANTIATE_TEST_SUITE_P(
	MatMulTests, MatMulTest,
	testing::Values(MatMulTestParam{{}, {}, {}},
					MatMulTestParam{{{}}, {{}}, {}},
					MatMulTestParam{{{1}}, {}, {}},
					MatMulTestParam{{{1}}, {{}}, {}},
					MatMulTestParam{{{2}}, {{3}}, {{6}}},
					MatMulTestParam{{{2}}, {{4}}, {{8}}},
					MatMulTestParam{{{2, 2}}, {{4}}, {}},
					MatMulTestParam{{{2}, {2}}, {{4}}, {{8}, {8}}},
					MatMulTestParam{{{4}}, {{2, 2}}, {{8, 8}}},
					MatMulTestParam{{{2, 2}}, {{2}, {2}}, {{8}}},
					MatMulTestParam{{{2, 2}}, {{2, 2}}, {}},
					MatMulTestParam{{{1, 2, 3}, {4, 5, 6}},
									{{1, 1, 1}, {2, 2, 2}, {3, 3, 3}},
									{
										{14, 14, 14},
										{32, 32, 32}}},
					MatMulTestParam{{{1, 2, 3}, {4, 5, 6}},
									{{1, 2, 3}, {1, 2, 3}, {1, 2, 3}},
									{
										{6, 12, 18},
										{15, 30, 45}}}
		)
	);
