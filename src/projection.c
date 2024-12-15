/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfreyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 18:38/58 by kfreyer           #+#    #+#             */
/*   Updated: 2024/12/13 18:38:58 by kfreyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

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

t_matrix	get_isometric_projection(t_map map)
{
	t_matrix	vectors;
	t_matrix	rot_matrix;
	t_matrix	isometric_projection;

	vectors = map_to_vectors(map);
	rot_matrix = get_rot_matrix();
	isometric_projection = mat_mul(rot_matrix, vectors);
	free_matrix(vectors);
	free_matrix(rot_matrix);
	return (isometric_projection);
}

/* translatation by minimum */
void	translate_vectors_to_first_octant(t_matrix *mat)
{
	t_extrema	extrema;

	extrema = get_extrema(*mat);
	translate_vectors(mat, -extrema.min_x, -extrema.min_y);
}

void	translate_vectors(t_matrix *mat, double x, double y)
{
	unsigned int	c2;

	c2 = 0;
	while (c2 < mat->n)
	{
		mat->mat[0][c2] += x;
		mat->mat[1][c2] += y;
		c2++;
	}
}

void	norm_vectors(t_matrix *mat)
{
	double	max_norm;
	double	norm;
	size_t	c1;
	double	x_squared;
	double	y_squared;

	max_norm = 0;
	norm = 0;
	c1 = 0;
	while (c1 < mat->n)
	{
		x_squared = pow(mat->mat[0][c1], 2);
		y_squared = pow(mat->mat[1][c1], 2);
		norm = sqrt(x_squared + y_squared);
		if (norm > max_norm)
			max_norm = norm;
		c1++;
	}
	scale_matrix(mat, 1 / max_norm);
}
