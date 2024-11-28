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
