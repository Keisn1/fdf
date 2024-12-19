/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_projection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfreyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 12:53/50 by kfreyer           #+#    #+#             */
/*   Updated: 2024/12/19 12:53:50 by kfreyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	change_projection(t_projection *p)
{
	if (p->kind == ISOMETRIC)
		p->kind = PARALLEL;
	else
		p->kind = ISOMETRIC;
	rebuild_projection(p);
}
