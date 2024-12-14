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

#include "matrix.h"

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

void	free_matrix(t_matrix M)
{
	unsigned int	m_count;

	m_count = 0;
	while (m_count < M.m)
		free(M.mat[m_count++]);
	free(M.mat);
}

