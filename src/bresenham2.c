/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfreyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 20:16/06 by kfreyer           #+#    #+#             */
/*   Updated: 2024/12/16 20:16:06 by kfreyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bresenham.h"

t_line	new_line(t_pixel px1, t_pixel px2, int col1, int col2)
{
	t_line	line;

	line.pixels[0] = (t_pixel){px1.x, px1.y};
	line.pixels[1] = (t_pixel){px2.x, px2.y};
	line.colors[0] = col1;
	line.colors[1] = col2;
	return (line);
}

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
