/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfreyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 11:32/02 by kfreyer           #+#    #+#             */
/*   Updated: 2024/10/28 11:32:02 by kfreyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"
#include <stdio.h>

int	lower(int x, int y)
{
	if (x < y)
	{
		return (1);
	}
	return (-1);
}

struct s_bres	new_bres(t_point p_0, t_point p_1)
{
	struct s_bres	ret;

	ret.dx = ft_abs(p_1.i - p_0.i);
	ret.dy = -ft_abs(p_1.j - p_0.j);
	ret.sx = lower(p_0.i, p_1.i);
	ret.sy = lower(p_0.j, p_1.j);
	ret.err = ret.dx + ret.dy;
	ret.e2 = 0;
	return (ret);
}

void	bres_plotline(t_mlx_data mlx_data, t_point p_0, t_point p_1,
		PixelPutFunc pixel_put)
{
	struct s_bres	bres;

	bres = new_bres(p_0, p_1);
	while (true)
	{
		pixel_put(mlx_data.mlx_ptr, mlx_data.win_ptr, p_0.i, p_0.j, 0xFF00FF);
		bres.e2 = 2 * bres.err;
		if (bres.e2 >= bres.dy)
		{
			if (p_0.i == p_1.i)
				break ;
			bres.err += bres.dy;
			p_0.i += bres.sx;
		}
		if (bres.e2 <= bres.dx)
		{
			if (p_0.j == p_1.j)
				break ;
			bres.err += bres.dx;
			p_0.j += bres.sy;
		}
	}
}

void	add_back_point(t_list **l, t_point p)
{
	t_point	*new;

	new = (t_point *)malloc(sizeof(t_point) * 1);
	new->i = p.i;
	new->j = p.j;
	ft_lstadd_back(l, ft_lstnew(new));
}

t_list	*get_bres_line(t_point p_0, t_point p_1)
{
	struct s_bres	bres;
	t_list			*points;

	bres = new_bres(p_0, p_1);
	points = NULL;
	while (true)
	{
		add_back_point(&points, p_0);
		bres.e2 = 2 * bres.err;
		if (bres.e2 >= bres.dy)
		{
			if (p_0.i == p_1.i)
				break ;
			bres.err += bres.dy;
			p_0.i += bres.sx;
		}
		if (bres.e2 <= bres.dx)
		{
			if (p_0.j == p_1.j)
				break ;
			bres.err += bres.dx;
			p_0.j += bres.sy;
		}
	}
	return (points);
}
