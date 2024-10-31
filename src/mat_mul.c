/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat_mul.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfreyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 10:45/49 by kfreyer           #+#    #+#             */
/*   Updated: 2024/10/31 10:45:49 by kfreyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

void print_matrix(double** matrix, unsigned int m, unsigned int n) {
	unsigned int i = 0;
	unsigned int j = 0;

	printf("m: %d\n", m);
	printf("n: %d\n", n);
	while (i < m) {
		j = 0;
		while (j < n) {
			printf("%f ", matrix[i][j]);
			j++;
		}

		printf("\n");
		i++;

	}
}

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
			mat[count_m][count_n] = 0;
			while (count_k < X.n)
			{
				mat[count_m][count_n] += X.mat[count_m][count_k] * Y.mat[count_k][count_n];
				count_k++;
			}
			/* mat[count_m][count_n] += ; */
			count_n++;
		}
		count_m++;
	}
	return ((t_mat){.mat = mat, .m = X.m, .n = Y.n});
}
