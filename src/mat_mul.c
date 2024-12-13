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
#include "matrix.h"
#include <math.h>

bool	valid_dimensions(t_matrix X, t_matrix Y)
{
	if (X.m == 0 || X.n == 0 || Y.m == 0 || Y.n == 0)
		return (false);
	if (X.n != Y.m)
		return (false);
	return (true);
}

t_matrix	mat_mul(t_matrix X, t_matrix Y)
{
	double			**mat;
	unsigned int	i;
	unsigned int	j;
	unsigned int	k;

	if (!valid_dimensions(X, Y))
		return ((t_matrix){NULL, 0, 0});
	mat = (double **)malloc(sizeof(double *) * X.m);
	i = 0;
	while (i < X.m)
	{
		mat[i] = (double *)malloc(sizeof(double) * Y.n);
		j = 0;
		while (j < Y.n)
		{
			k = 0;
			mat[i][j] = 0;
			while (k++ < X.n)
				mat[i][j] += X.mat[i][k - 1] * Y.mat[k - 1][j];
			j++;
		}
		i++;
	}
	return ((t_matrix){.mat = mat, .m = X.m, .n = Y.n});
}

t_matrix	get_rot_matrix(void)
{
	t_matrix	rot_matrix;

	rot_matrix.m = 2;
	rot_matrix.n = 3;
	rot_matrix.mat = (double **)malloc(sizeof(double *) * rot_matrix.m);
	rot_matrix.mat[0] = (double *)malloc(sizeof(double *) * rot_matrix.n);
	rot_matrix.mat[1] = (double *)malloc(sizeof(double *) * rot_matrix.n);
	rot_matrix.mat[0][0] = 1. / sqrt(2);
	rot_matrix.mat[0][1] = -1. / sqrt(2);
	rot_matrix.mat[0][2] = 0;
	rot_matrix.mat[1][0] = 1. / sqrt(6);
	rot_matrix.mat[1][1] = 1. / sqrt(6);
	rot_matrix.mat[1][2] = -sqrt(2.) / sqrt(3);
	return (rot_matrix);
}
