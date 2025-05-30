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

int	get_nbr_of_steps(t_line line)
{
	if (ft_abs((int)line.pixels[1].y
			- (int)line.pixels[0].y) < ft_abs((int)line.pixels[1].x
			- (int)line.pixels[0].x))
		return (ft_abs((int)line.pixels[1].x - (int)line.pixels[0].x));
	return (ft_abs((int)line.pixels[1].y - (int)line.pixels[0].y));
}

void	bres_update1(t_line *line, t_bresenham *bres)
{
	bres->err += bres->dy;
	line->pixels[0].x += bres->sx;
}

void	bres_update2(t_line *line, t_bresenham *bres)
{
	bres->err += bres->dx;
	line->pixels[0].y += bres->sy;
}

void	bres_plotline_img(t_mlx_data mlx_data, t_img *img, t_line line,
		t_img_put_pixel_func ipp)
{
	t_bresenham	bres;
	float		g_step[3];
	float		c[3];

	extract_rgb(line.colors[0], c);
	fill_grad_step(g_step, line, get_nbr_of_steps(line));
	bres = new_bres(line.pixels[0], line.pixels[1]);
	while (true)
	{
		ipp(mlx_data.mlx_ptr, img, line.pixels[0], add_g_step(c, g_step));
		bres.e2 = 2 * bres.err;
		if (bres.e2 >= bres.dy)
		{
			if (line.pixels[0].x == line.pixels[1].x)
				break ;
			bres_update1(&line, &bres);
		}
		if (bres.e2 <= bres.dx)
		{
			if (line.pixels[0].y == line.pixels[1].y)
				break ;
			bres_update2(&line, &bres);
		}
	}
}
