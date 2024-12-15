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

#include "bresenham.h"
#include "libft.h"
#include "my_mlx.h"

t_bresenham	new_bres(t_pixel p_0, t_pixel p_1)
{
	t_bresenham	ret;

	ret.dx = ft_abs(p_1.i - p_0.i);
	ret.dy = -ft_abs(p_1.j - p_0.j);
	if (p_0.i < p_1.i)
		ret.sx = 1;
	else
		ret.sx = -1;
	if (p_0.j < p_1.j)
		ret.sy = 1;
	else
		ret.sy = -1;
	ret.err = ret.dx + ret.dy;
	ret.e2 = 0;
	return (ret);
}

t_line	new_line(t_pixel px1, t_pixel px2)
{
	t_line	line;

	line.pixels[0] = (t_pixel){px1.i, px1.j};
	line.pixels[1] = (t_pixel){px2.i, px2.j};
	line.colors[0] = 0xFF00FF;
	line.colors[1] = 0xFF00FF;
	return (line);
}

void	bres_plotline_img(t_mlx_data mlx_data, t_img *img, t_line line,
		t_img_put_pixel_func t_img_put_pixel)
{
	t_bresenham	bres;

	bres = new_bres(line.pixels[0], line.pixels[1]);
	while (true)
	{
		t_img_put_pixel(mlx_data.mlx_ptr, img, line.pixels[0], line.colors[0]);
		bres.e2 = 2 * bres.err;
		if (bres.e2 >= bres.dy)
		{
			if (line.pixels[0].i == line.pixels[1].i)
				break ;
			bres.err += bres.dy;
			line.pixels[0].i += bres.sx;
		}
		if (bres.e2 <= bres.dx)
		{
			if (line.pixels[0].j == line.pixels[1].j)
				break ;
			bres.err += bres.dx;
			line.pixels[0].j += bres.sy;
		}
	}
}
