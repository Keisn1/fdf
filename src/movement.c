/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfreyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 11:27/27 by kfreyer           #+#    #+#             */
/*   Updated: 2024/11/01 11:27:27 by kfreyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

double	ft_abs_double(double x)
{
	if (x < 0)
		return (-x);
	return (x);
}

/* takes 2xn Matrix */
/* returns min max of rows*/
t_limits get_limits(t_matrix M)
{
	if (M.m == 0)
		return (t_limits){0, 0, 0, 0};

	t_limits limits = {M.mat[0][0], M.mat[1][0], M.mat[0][0], M.mat[1][0]};
	double x;
	double y;

	unsigned int count = 1;
	while (count < M.n) {
		x = M.mat[0][count];
		y = M.mat[1][count];

		if (x < limits.min_x)
			limits.min_x = x;
		if (y < limits.min_y)
			limits.min_y = y;
		if (x > limits.max_x)
			limits.max_x = x;
		if (y > limits.max_y)
			limits.max_y = y;
		count++;
	}
	return limits;
}

/* scaling down so that everything fits into size_x and size_y */
unsigned int get_scale(unsigned int size_x, unsigned int size_y, t_limits limits){
	double max_abs_x;
	double max_abs_y;

	max_abs_x = ft_abs_double(limits.max_x);
	if (max_abs_x < ft_abs_double(limits.min_x))
		max_abs_x = ft_abs_double(limits.min_x);

	max_abs_y = ft_abs_double(limits.max_y);
	if (max_abs_y < ft_abs_double(limits.min_y))
		max_abs_y = ft_abs_double(limits.min_y);


	unsigned int scale_x = size_x/max_abs_x;
	unsigned int scale_y = size_y/max_abs_y;
	if (scale_x < scale_y)
		return scale_x;
	return scale_y;
}
