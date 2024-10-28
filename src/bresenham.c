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

int	lt(int x, int y)
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

	ret.dx = ft_abs(p_1.x - p_0.x);
	ret.dy = -ft_abs(p_1.y - p_0.y);
	ret.sx = lt(p_0.x, p_1.x);
	ret.sy = lt(p_0.y, p_1.y);
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
		pixel_put(mlx_data.mlx_ptr, mlx_data.win_ptr, p_0.x, p_0.y, 0xFF00FF);
		bres.e2 = 2 * bres.err;
		if (bres.e2 >= bres.dy)
		{
			if (p_0.x == p_1.x)
				break ;
			bres.err += bres.dy;
			p_0.x += bres.sx;
		}
		if (bres.e2 <= bres.dx)
		{
			if (p_0.y == p_1.y)
				break ;
			bres.err += bres.dx;
			p_0.y += bres.sy;
		}
	}
}
