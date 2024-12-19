/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfreyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 12:05/53 by kfreyer           #+#    #+#             */
/*   Updated: 2024/12/13 12:05:53 by kfreyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIX_H
# define MATRIX_H

# include <stdlib.h>
# include <stdbool.h>

typedef struct s_mat
{
	double			**mat;
	unsigned int	m;
	unsigned int	n;
}					t_matrix;

void				free_matrix(t_matrix M);
t_matrix			mat_mul(t_matrix X, t_matrix Y);

typedef struct s_extrema
{
	double			min_x;
	double			min_y;
	double			max_x;
	double			max_y;
}					t_extrema;
t_extrema			get_extrema(t_matrix M);

void				scale_matrix(t_matrix *m, double scale);
#endif // MATRIX_H
