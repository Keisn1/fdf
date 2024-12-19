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
#include "matrix.h"
#include <math.h>

t_matrix	get_rot_matrix_z(double drehwinkel)
{
	t_matrix	rot_matrix;
	double		theta;

	theta = (M_PI / 180.0) * drehwinkel;
	rot_matrix.m = 3;
	rot_matrix.n = 3;
	rot_matrix.mat = (double **)malloc(sizeof(double *) * rot_matrix.m);
	rot_matrix.mat[0] = (double *)malloc(sizeof(double *) * rot_matrix.n);
	rot_matrix.mat[1] = (double *)malloc(sizeof(double *) * rot_matrix.n);
	rot_matrix.mat[2] = (double *)malloc(sizeof(double *) * rot_matrix.n);
	rot_matrix.mat[0][0] = cos(theta);
	rot_matrix.mat[0][1] = -sin(theta);
	rot_matrix.mat[0][2] = 0;
	rot_matrix.mat[1][0] = sin(theta);
	rot_matrix.mat[1][1] = cos(theta);
	rot_matrix.mat[1][2] = 0;
	rot_matrix.mat[2][0] = 0;
	rot_matrix.mat[2][1] = 0;
	rot_matrix.mat[2][2] = 1;
	return (rot_matrix);
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
	pp_matrix.mat[1][2] = 1;
	return (pp_matrix);
}

t_matrix	get_isometric_projection(t_matrix vectors)
{
	t_matrix	rot_matrix;
	t_matrix	isometric_projection;

	rot_matrix = get_rot_matrix();
	isometric_projection = mat_mul(rot_matrix, vectors);
	free_matrix(rot_matrix);
	return (isometric_projection);
}

t_matrix	get_parallel_projection(t_matrix vectors)
{
	t_matrix	pp_matrix;
	t_matrix	parallel_projection;

	pp_matrix = get_rot_matrix();
	parallel_projection = mat_mul(pp_matrix, vectors);
	free_matrix(pp_matrix);
	return (parallel_projection);
}

/* /\* translatation by minimum *\/ */
/* void	translate_vectors_to_first_octant(t_matrix *mat) */
/* { */
/* 	t_extrema	extrema; */

/* 	extrema = get_extrema(*mat); */
/* 	translate_vectors(mat, -extrema.min_x, -extrema.min_y); */
/* } */

void	translate_projection(t_matrix *mat, int x, int y)
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
	double	z_squared;

	max_norm = 0;
	norm = 0;
	c1 = 0;
	while (c1 < mat->n)
	{
		x_squared = pow(mat->mat[0][c1], 2);
		y_squared = pow(mat->mat[1][c1], 2);
		z_squared = pow(mat->mat[1][c1], 2);
		norm = sqrt(x_squared + y_squared + z_squared);
		if (norm > max_norm)
			max_norm = norm;
		c1++;
	}
	scale_matrix(mat, 1 / max_norm);
}

double	ft_abs_double(double x)
{
	if (x < 0)
		return (-x);
	return (x);
}

double	get_init_scale(t_matrix projection, double width, double height)
{
	t_extrema	e;
	double		max_y;
	double		max_x;
	double		init_scale;

	e = get_extrema(projection);
	max_y = ft_abs_double(e.max_y) > ft_abs_double(e.min_y) ? ft_abs_double(e.max_y) : ft_abs_double(e.min_y);
	max_x = ft_abs_double(e.max_x) > ft_abs_double(e.min_x) ? ft_abs_double(e.max_x) : ft_abs_double(e.min_x);
	init_scale = width / 2.1 / max_x;
	if (height / 2.1 / max_y < init_scale)
		init_scale = height / 2.1 / max_y;
	return (init_scale);
}

t_projection	new_projection(char *filename, double width, double height)
{
	t_projection	p;
	t_map			map;

	map = parse_map(filename);
	p.drehwinkel = 2;
	p.zoom_factor = 1.02;
	p.zoom = 0;
	p.rotation = 0;
	p.translation_h = 0;
	p.translation_v = 0;
	p.last_pos_x = 0;
	p.last_pos_y = 0;
	p.rows = map.map.m;
	p.cols = map.map.n;
	p.vectors = map_to_vectors(map);
	norm_vectors(&p.vectors);
	p.projection = get_isometric_projection(p.vectors);
	p.colors = map.colors;
	p.init_scale = get_init_scale(p.projection, width, height);
	scale_matrix(&p.projection, p.init_scale);
	free_matrix(map.map);
	return (p);
}
