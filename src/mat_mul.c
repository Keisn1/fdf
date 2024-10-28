#include "fdf.h"
#include <stddef.h>
#include <stdlib.h>

t_mat mat_mul(t_mat X, t_mat Y) {
	if (X.m == 0 || X.n == 0 || Y.m == 0 || Y.n == 0)
		return (t_mat){NULL, 0, 0};

	if (X.n != Y.m)
		return (t_mat){NULL, 0, 0};

	int** mat = (int**)malloc(sizeof(int*) * X.m);
	int count_m = 0;
	while (count_m < X.m) {
		mat[count_m] = (int*)malloc(sizeof(int) * Y.n);
		int count_n = 0;
		while (count_n < Y.n) {
			mat[count_m][count_n] = X.mat[count_m][0] * Y.mat[0][count_n];
			count_n++;
		}
		count_m++;
	}

	return (t_mat){.mat = mat, .m = X.m, .n = Y.n};;
}
