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
#include <math.h>

t_matrix	mat_mul(t_matrix X, t_matrix Y)
{
	double	**mat;
	unsigned int		count_m;
	unsigned int		count_n;
	unsigned int		count_k;

	if (X.m == 0 || X.n == 0 || Y.m == 0 || Y.n == 0)
		return ((t_matrix){NULL, 0, 0});
	if (X.n != Y.m)
		return ((t_matrix){NULL, 0, 0});
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
				mat[count_m][count_n] += X.mat[count_m][count_k]
					* Y.mat[count_k][count_n];
				count_k++;
			}
			count_n++;
		}
		count_m++;
	}
	return ((t_matrix){.mat = mat, .m = X.m, .n = Y.n});
}

t_matrix	get_rot_matrix(void)
{
	t_matrix	rot_M;

	rot_M.m = 2;
	rot_M.n = 3;
	rot_M.mat = (double **)malloc(sizeof(double *) * rot_M.m);
	rot_M.mat[0] = (double *)malloc(sizeof(double *) * rot_M.n);
	rot_M.mat[1] = (double *)malloc(sizeof(double *) * rot_M.n);
	rot_M.mat[0][0] = 1. / sqrt(2);
	rot_M.mat[0][1] = -1. / sqrt(2);
	rot_M.mat[0][2] = 0;
	rot_M.mat[1][0] = 1. / sqrt(6);
	rot_M.mat[1][1] = 1. / sqrt(6);
	rot_M.mat[1][2] = -sqrt(2.) / sqrt(3);
	return (rot_M);
}
