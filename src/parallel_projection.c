/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parallel_projection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfreyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 12:47/27 by kfreyer           #+#    #+#             */
/*   Updated: 2024/12/19 12:47:27 by kfreyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_matrix	get_pp_matrix(void)
{
	t_matrix	pp_matrix;

	pp_matrix.m = 2;
	pp_matrix.n = 3;
	pp_matrix.mat = (double **)malloc(sizeof(double *) * pp_matrix.m);
	pp_matrix.mat[0] = (double *)malloc(sizeof(double *) * pp_matrix.n);
	pp_matrix.mat[1] = (double *)malloc(sizeof(double *) * pp_matrix.n);
	pp_matrix.mat[0][0] = 1;
	pp_matrix.mat[0][1] = 0;
	pp_matrix.mat[0][2] = 0;
	pp_matrix.mat[1][0] = 0;
	pp_matrix.mat[1][1] = 0;
	pp_matrix.mat[1][2] = -1;
	return (pp_matrix);
}

t_matrix	get_parallel_projection(t_matrix vectors)
{
	t_matrix	pp_matrix;
	t_matrix	parallel_projection;

	pp_matrix = get_pp_matrix();
	parallel_projection = mat_mul(pp_matrix, vectors);
	free_matrix(pp_matrix);
	return (parallel_projection);
}
