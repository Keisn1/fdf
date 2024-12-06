#include "test_fdf.hpp"

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

t_matrix new_matrix(std::vector<std::vector<double>> A) {
	t_matrix M;
	M.mat = create_matrix(A);
	M.m = A.size();
	if (A.size() == 0) {
		M.n = 0;
		return M;
	}
	M.n = A[0].size();
	return M;
}
