/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfreyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 12:37/20 by kfreyer           #+#    #+#             */
/*   Updated: 2024/12/19 12:37:20 by kfreyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
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

void	rotate_left(t_projection *p)
{
	t_matrix	rotation_z;
	t_matrix	rotated_vectors;

	p->rotation++;
	rotation_z = get_rot_matrix_z(p->rotation * p->drehwinkel);
	rotated_vectors = mat_mul(rotation_z, p->vectors);
	free_matrix(rotation_z);
	free_matrix(p->projection);
	if (p->kind == ISOMETRIC)
		p->projection = get_isometric_projection(rotated_vectors);
	else if (p->kind == PARALLEL)
		p->projection = get_parallel_projection(rotated_vectors);
	free_matrix(rotated_vectors);
	scale_matrix(&p->projection, p->init_scale * pow(p->zoom_factor, p->zoom));
	translate_projection(&p->projection, p->translation_h , p->translation_v );
}

void	rotate_right(t_projection *p)
{
	t_matrix	rotation_z;
	t_matrix	rotated_vectors;

	p->rotation--;
	rotation_z = get_rot_matrix_z(p->rotation * p->drehwinkel);
	rotated_vectors = mat_mul(rotation_z, p->vectors);
	free_matrix(rotation_z);
	free_matrix(p->projection);
	if (p->kind == ISOMETRIC)
		p->projection = get_isometric_projection(rotated_vectors);
	else if (p->kind == PARALLEL)
		p->projection = get_parallel_projection(rotated_vectors);
	free_matrix(rotated_vectors);
	scale_matrix(&p->projection, p->init_scale * pow(p->zoom_factor, p->zoom));
	translate_projection(&p->projection, p->translation_h , p->translation_v );
}
