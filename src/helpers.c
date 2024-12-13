/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   by: kfreyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   created: 2024/12/12 22:48/53 by kfreyer           #+#    #+#             */
/*   updated: 2024/12/12 22:48:53 by kfreyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"
#include <stdlib.h>

void	free_matrix(t_matrix M)
{
	unsigned int	m_count;

	m_count = 0;
	while (m_count < M.m)
		free(M.mat[m_count++]);
	free(M.mat);
}
