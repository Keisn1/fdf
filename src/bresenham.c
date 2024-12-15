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

	ret.dx = ft_abs(p_1.x - p_0.x);
	ret.dy = -ft_abs(p_1.y - p_0.y);
	if (p_0.x < p_1.x)
		ret.sx = 1;
	else
		ret.sx = -1;
	if (p_0.y < p_1.y)
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

	line.pixels[0] = (t_pixel){px1.x, px1.y};
	line.pixels[1] = (t_pixel){px2.x, px2.y};
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
			if (line.pixels[0].x == line.pixels[1].x)
				break ;
			bres.err += bres.dy;
			line.pixels[0].x += bres.sx;
		}
		if (bres.e2 <= bres.dx)
		{
			if (line.pixels[0].y == line.pixels[1].y)
				break ;
			bres.err += bres.dx;
			line.pixels[0].y += bres.sy;
		}
	}
}

void bres_plotine_simple(t_mlx_data mlx_data, t_img *img, t_line line, t_img_put_pixel_func t_img_put_pixel) {
	t_pixel p0 = line.pixels[0];
	t_pixel p1 = line.pixels[1];

	int dx = p1.x - p0.x;
	int dy = p1.y - p0.y;
	int D = 2 * dy - dx;

	while (p0.x <= p1.x) {
		t_img_put_pixel(mlx_data.mlx_ptr, img, p0, line.colors[0]);
		if (D > 0) {
			p0.y++;
			D = D - 2*dx;
		}
		D = D + 2*dy;
	}
}
