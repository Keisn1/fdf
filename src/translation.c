/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfreyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 12:34/40 by kfreyer           #+#    #+#             */
/*   Updated: 2024/12/19 12:34:40 by kfreyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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

void	translate_left(t_projection *p)
{
	p->translation_h--;
	translate_projection(&p->projection, -1, 0);
}
void	translate_right(t_projection *p)
{
	p->translation_h++;
	translate_projection(&p->projection, 1, 0);
}
void	translate_up(t_projection *p)
{
	p->translation_v--;
	translate_projection(&p->projection, 0, -1);
}
void	translate_down(t_projection *p)
{
	p->translation_v++;
	translate_projection(&p->projection, 0, 1);
}
