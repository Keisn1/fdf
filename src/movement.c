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

#include "matrix.h"

/* takes 2xn Matrix */
/* returns min max of rows*/
t_extrema	get_extrema(t_matrix M)
{
	t_extrema		limits;
	double			x;
	double			y;
	unsigned int	count;

	if (M.m == 0)
		return ((t_extrema){0, 0, 0, 0});
	limits = (t_extrema){M.mat[0][0], M.mat[1][0], M.mat[0][0], M.mat[1][0]};
	count = 1;
	while (count < M.n)
	{
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
	return (limits);
}
