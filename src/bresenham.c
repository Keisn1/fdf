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

int get_nbr_of_steps(t_line line)
{
	if (ft_abs((int)line.pixels[1].y - (int)line.pixels[0].y) < ft_abs((int)line.pixels[1].x - (int)line.pixels[0].x))
		return  ft_abs((int)line.pixels[1].x - (int)line.pixels[0].x);
	return ft_abs((int)line.pixels[1].y - (int)line.pixels[0].y);
}

// Function to extract RGB components
void extractRGB(int color, int *red, int *green, int *blue) {
	*red = (color >> 16) & 0xFF;
	*green = (color >> 8) & 0xFF;
	*blue = color & 0xFF;
}

int calculate_color(t_line line, int steps, int step) {

	int color1 = line.colors[0]; // Red
	int color2 = line.colors[1]; // Green

	// Extract initial RGB components
	int r1, g1, b1;
	int r2, g2, b2;
	extractRGB(color1, &r1, &g1, &b1);
	extractRGB(color2, &r2, &g2, &b2);

	// Calculate step increments
	float stepR = (r2 - r1) / (float)steps;
	float stepG = (g2 - g1) / (float)steps;
	float stepB = (b2 - b1) / (float)steps;

	int red = r1 + stepR * step;
	int green = g1 + stepG * step;
	int blue = b1 + stepB * step;

	return (red << 16) | (green << 8) | blue;

}

void	bres_plotline_img(t_mlx_data mlx_data, t_img *img, t_line line,
		t_img_put_pixel_func t_img_put_pixel)
{
	t_bresenham	bres;
	int count = 0;
	int color;
	int steps = get_nbr_of_steps(line);

	bres = new_bres(line.pixels[0], line.pixels[1]);
	while (true)
	{
		color = calculate_color(line, steps, count);
		count++;
		t_img_put_pixel(mlx_data.mlx_ptr, img, line.pixels[0], color);
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

void	bres_plotline_low(t_mlx_data mlx_data, t_img *img, t_line line,
		t_img_put_pixel_func img_put_pixel)
{
	t_pixel	p0;
	t_pixel	p1;
	int		dx;
	int		dy;
	int		yi;
	int		D;

	p0 = line.pixels[0];
	p1 = line.pixels[1];
	dx = p1.x - p0.x;
	dy = p1.y - p0.y;
	yi = 1;
	if (dy < 0)
	{
		yi = -1;
		dy = -dy;
	}
	D = (2 * dy) - dx;
	while (p0.x <= p1.x)
	{
		img_put_pixel(mlx_data.mlx_ptr, img, p0, line.colors[0]);
		if (D > 0)
		{
			p0.y += yi;
			D += 2 * (dy - dx);
		}
		else
			D += 2 * dy;
		p0.x++;
	}
}

void	bres_plotline_high(t_mlx_data mlx_data, t_img *img, t_line line,
		t_img_put_pixel_func img_put_pixel)
{
	t_pixel	p0;
	t_pixel	p1;
	int		dx;
	int		dy;
	int		xi;
	int		D;

	p0 = line.pixels[0];
	p1 = line.pixels[1];
	dx = p1.x - p0.x;
	dy = p1.y - p0.y;
	xi = 1;
	if (dx < 0)
	{
		xi = -1;
		dx = -dx;
	}
	D = (2 * dx) - dy;
	while (p0.y <= p1.y)
	{
		img_put_pixel(mlx_data.mlx_ptr, img, p0, line.colors[0]);
		if (D > 0)
		{
			p0.x += xi;
			D += 2 * (dx - dy);
		}
		else
			D += 2 * dx;
		p0.y++;
	}
}

void	switch_points(t_line *line)
{
	t_pixel	tmp;

	tmp = line->pixels[0];
	line->pixels[0] = line->pixels[1];
	line->pixels[1] = tmp;
	return ;
}

void	bres_plotline_simple(t_mlx_data mlx_data, t_img *img, t_line line,
		t_img_put_pixel_func img_put_pixel)
{
	if (abs((int)line.pixels[1].y
			- (int)line.pixels[0].y) < abs((int)line.pixels[1].x
			- (int)line.pixels[0].x))
	{
		if (line.pixels[0].x > line.pixels[1].x)
		{
			switch_points(&line);
			bres_plotline_low(mlx_data, img, line, img_put_pixel);
		}
		else
			bres_plotline_low(mlx_data, img, line, img_put_pixel);
	}
	else
	{
		if (line.pixels[0].y > line.pixels[1].y)
		{
			switch_points(&line);
			bres_plotline_high(mlx_data, img, line, img_put_pixel);
		}
		else
			bres_plotline_high(mlx_data, img, line, img_put_pixel);
	}
}
