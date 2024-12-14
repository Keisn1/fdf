/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfreyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 11:55/51 by kfreyer           #+#    #+#             */
/*   Updated: 2024/12/14 11:55:51 by kfreyer          ###   ########.fr       */
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
