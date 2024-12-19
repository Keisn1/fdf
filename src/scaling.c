/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scaling.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfreyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 12:39/43 by kfreyer           #+#    #+#             */
/*   Updated: 2024/12/19 12:39:43 by kfreyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	scale_up(t_projection *p)
{
	p->zoom++;
	scale_matrix(&p->projection, p->zoom_factor);
	p->translation_h = p->translation_h * p->zoom_factor;
	p->translation_v = p->translation_v * p->zoom_factor;
}

void	scale_down(t_projection *p)
{
	p->zoom--;
	scale_matrix(&p->projection, 1 / p->zoom_factor);
	p->translation_h = p->translation_h / p->zoom_factor;
	p->translation_v = p->translation_v / p->zoom_factor;
}
