#include "test_fdf.hpp"


// void expect_equal_points(t_points want, t_points got) {
// 	EXPECT_EQ(want.length, got.length);
// 	size_t count = 0;
// 	while (count < want.length) {
// 		EXPECT_EQ(want.points[count].x, got.points[count].x);
// 		EXPECT_EQ(want.points[count].y, got.points[count].y);
// 		count++;
// 	}
// }

double **create_matrix(std::vector<std::vector<double>> M) {
	int m = M.size();
	if (m == 0)
		return NULL;

	int n = M[0].size();

	double** ret = (double**)malloc(sizeof(double*) * m);
	if (!ret)
		return NULL;
	for (int i = 0; i < m; i++) {
		double* line = (double*)malloc(sizeof(double) * n);
		if (!line)
			return NULL;
		for (int j = 0; j < n; j++)
			line[j] = M[i][j];
		ret[i] = line;
	}
	return ret;
};
