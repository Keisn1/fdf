/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham_not_used.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfreyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 18:10/20 by kfreyer           #+#    #+#             */
/*   Updated: 2024/12/15 18:10:20 by kfreyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bresenham.h"
#include "my_mlx.h"

void	add_px_to_list(t_list **pixels, t_pixel p)
{
	t_pixel	*new;

	new = (t_pixel *)malloc(sizeof(t_pixel) * 1);
	new->x = p.x;
	new->y = p.y;
	ft_lstadd_back(pixels, ft_lstnew(new));
}

t_list	*get_bres_line(t_line line)
{
	t_bresenham	bres;
	t_list		*pixels;

	bres = new_bres(line.pixels[0], line.pixels[1]);
	pixels = NULL;
	while (true)
	{
		add_px_to_list(&pixels, line.pixels[0]);
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
	return (pixels);
}

void	bres_plotline_img_with_list(t_mlx_data mlx_data, t_img *img, t_line line, t_img_put_pixel_func img_put_pixel) {
	t_list	*pixels;
	t_list	*head;

	pixels = get_bres_line(line);
	head = pixels;
	while (head)
	{
		img_put_pixel(mlx_data.mlx_ptr, img, *(t_pixel *)head->content,
			0xFF00FF);
		head = head->next;
	}
	ft_lstclear(&pixels, free);
}

void	bres_plotline_window(t_mlx_data mlx_data, t_pixel p_0, t_pixel p_1,
		t_pixel_put_func pixel_put)
{
	t_bresenham	bres;

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
