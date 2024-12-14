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

#include "libft.h"

typedef struct s_mat
{
	double			**mat;
	unsigned int	m;
	unsigned int	n;
}					t_matrix;

void				free_matrix(t_matrix M);
t_matrix			mat_mul(t_matrix X, t_matrix Y);

#endif // MATRIX_H
