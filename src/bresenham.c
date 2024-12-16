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
#include <unistd.h>

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

t_line	new_line(t_pixel px1, t_pixel px2, int col1, int col2)
{
	t_line	line;

	line.pixels[0] = (t_pixel){px1.x, px1.y};
	line.pixels[1] = (t_pixel){px2.x, px2.y};
	line.colors[0] = col1;
	line.colors[1] = col2;
	return (line);
}

int	get_nbr_of_steps(t_line line)
{
	if (ft_abs((int)line.pixels[1].y
			- (int)line.pixels[0].y) < ft_abs((int)line.pixels[1].x
			- (int)line.pixels[0].x))
		return (ft_abs((int)line.pixels[1].x - (int)line.pixels[0].x));
	return (ft_abs((int)line.pixels[1].y - (int)line.pixels[0].y));
}

// Function to extract RGB components
void	extract_rgb(int color, float rgb[3])
{
	rgb[0] = (color >> 16) & 0xFF;
	rgb[1] = (color >> 8) & 0xFF;
	rgb[2] = color & 0xFF;
}

void	fill_grad_step(float grad_step[3], t_line line, int steps)
{
	float	rgb1[3];
	float	rgb2[3];

	extract_rgb(line.colors[0], rgb1);
	extract_rgb(line.colors[1], rgb2);
	grad_step[0] = (rgb2[0] - rgb1[0]) / (float)steps;
	grad_step[1] = (rgb2[1] - rgb1[1]) / (float)steps;
	grad_step[2] = (rgb2[2] - rgb1[2]) / (float)steps;
}

int	add_g_step(float color[3], float grad_step[3])
{
	color[0] = color[0] + grad_step[0];
	color[1] = color[1] + grad_step[1];
	color[2] = color[2] + grad_step[2];
	return (((int)color[0] << 16) | ((int)color[1] << 8) | (int)color[2]);
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
