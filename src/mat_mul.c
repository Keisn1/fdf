#include "fdf.h"
#include <stddef.h>
#include <stdlib.h>

t_mat	mat_mul(t_mat X, t_mat Y)
{
	double	**mat;
	int		count_m;
	int		count_n;
	int		count_k;

	if (X.m == 0 || X.n == 0 || Y.m == 0 || Y.n == 0)
		return ((t_mat){NULL, 0, 0});
	if (X.n != Y.m)
		return ((t_mat){NULL, 0, 0});
	mat = (double **)malloc(sizeof(double *) * X.m);
	count_m = 0;
	while (count_m < X.m)
	{
		mat[count_m] = (double *)malloc(sizeof(double) * Y.n);
		count_n = 0;
		while (count_n < Y.n)
		{
			count_k = 0;
			while (count_k < X.n)
			{
				mat[count_m][count_n] = X.mat[count_m][count_k]
					* Y.mat[count_k][count_n];
				count_k++;
			}
			count_n++;
		}
		count_m++;
	}
	return ((t_mat){.mat = mat, .m = X.m, .n = Y.n});
	;
}
