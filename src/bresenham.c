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
void	extractRGB(int color, float rgb[3])
{
	rgb[0] = (color >> 16) & 0xFF;
	rgb[1] = (color >> 8) & 0xFF;
	rgb[2] = color & 0xFF;
}

void	fill_grad_step(float grad_step[3], t_line line, int steps)
{
	float	rgb1[3];
	float	rgb2[3];

	extractRGB(line.colors[0], rgb1);
	extractRGB(line.colors[1], rgb2);
	grad_step[0] = (rgb2[0] - rgb1[0]) / (float)steps;
	grad_step[1] = (rgb2[1] - rgb1[1]) / (float)steps;
	grad_step[2] = (rgb2[2] - rgb1[2]) / (float)steps;
}

int	calculate_color(float color[3], float grad_step[3], int step)
{
	int	red;
	int	green;
	int	blue;

	red = color[0] + grad_step[0] * step;
	green = color[1] + grad_step[1] * step;
	blue = color[2] + grad_step[2] * step;
	return ((red << 16) | (green << 8) | blue);
}

void	bres_plotline_img(t_mlx_data mlx_data, t_img *img, t_line line,
		t_img_put_pixel_func img_put_pixel)
{
	t_bresenham	bres;
	int			step;
	float		grad_step[3];
	float		color[3];

	step = 0;
	extractRGB(line.colors[0], color);
	fill_grad_step(grad_step, line, get_nbr_of_steps(line));
	bres = new_bres(line.pixels[0], line.pixels[1]);
	while (true)
	{
		img_put_pixel(mlx_data.mlx_ptr, img, line.pixels[0], calculate_color(color, grad_step, step++));
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
