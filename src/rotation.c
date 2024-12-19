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
	p->rotation++;
	rebuild_projection(p);
}

void	rotate_right(t_projection *p)
{
	p->rotation--;
	rebuild_projection(p);
}
