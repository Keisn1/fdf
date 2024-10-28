#include "fdf.h"
#include "gtest/gtest.h"
#include <gtest/gtest.h>
#include <vector>

struct MatMulTestParam {
	std::vector<std::vector<int>> X;
	std::vector<std::vector<int>> Y;
	std::vector<std::vector<int>> want;
};

class MatMulTest : public testing::TestWithParam<MatMulTestParam> {};

int **create_matrix(std::vector<std::vector<int>> M) {
	int m = M.size();
	if (m == 0)
		return NULL;

	int n = M[0].size();

	int** ret = (int**)malloc(sizeof(int*) * m);
	if (!ret)
		return NULL;
	for (int i = 0; i < m; i++) {
		int* line = (int*)malloc(sizeof(int) * n);
		if (!line)
			return NULL;
		for (int j = 0; j < n; j++)
			line[j] = M[i][j];
		ret[i] = line;
	}
	return ret;
};

t_mat new_matrix(std::vector<std::vector<int>> A) {
	t_mat M;
	M.mat = create_matrix(A);
	M.m = A.size();
	if (A.size() == 0) {
		M.n = 0;
		return M;
	}
	M.n = A[0].size();
	return M;
}

TEST_P(MatMulTest, MatMulTest) {
	MatMulTestParam params = GetParam();
	t_mat X = new_matrix(params.X);
	t_mat Y = new_matrix(params.Y);
	t_mat want = new_matrix(params.want);

	t_mat got = mat_mul(X, Y);

	std::cout << X.n << "  " << Y.m << '\n';
	EXPECT_EQ(want.m, got.m);
	EXPECT_EQ(want.n, got.n);
	// for (int i = 0; i < want.m ; i++) {
	// 	for (int j = 0; j < want.n ; j++) {
	// 		std::cout << "i: " << i << " j: " << j << '\n';
	// 		EXPECT_EQ(want.mat[i][j], got.mat[i][j]);
	// 	}
	// }

	free_matrix(X);
	free_matrix(Y);
	free_matrix(want);
	free_matrix(got);
}

INSTANTIATE_TEST_SUITE_P(
	MatMulTests,
	MatMulTest,
	testing::Values(
		MatMulTestParam{{}, {}, {}},
		MatMulTestParam{{{}}, {{}}, {}},
		MatMulTestParam{{{1}}, {}, {}},
		MatMulTestParam{{{1}}, {{}}, {}},
		MatMulTestParam{{{2}}, {{3}}, {{6}}},
		MatMulTestParam{{{2}}, {{4}}, {{8}}},
		MatMulTestParam{{{2, 2}}, {{4}}, {}},
		MatMulTestParam{{{2},{2}}, {{4}}, {{8}, {8}}},
		MatMulTestParam{{{4}}, {{2, 2}}, {{8, 8}}}
		)
	);
