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

t_bres	new_bres(t_pixel p_0, t_pixel p_1)
{
	t_bres	ret;

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

void	bres_plotline_img(t_mlx_data mlx_data, t_pixel p_0, t_pixel p_1,
		t_img *img)
{
	t_bres	bres;

	bres = new_bres(p_0, p_1);
	while (true)
	{
		img_put_pixel(mlx_data.mlx_ptr, img, p_0, 0xFF00FF);
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

void	bres_plotline(t_mlx_data mlx_data, t_pixel p_0, t_pixel p_1,
		t_pixel_put_func pixel_put)
{
	t_bres	bres;

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

void	add_px_to_list(t_list **pixels, t_pixel p)
{
	t_pixel	*new;

	new = (t_pixel *)malloc(sizeof(t_pixel) * 1);
	new->i = p.i;
	new->j = p.j;
	ft_lstadd_back(pixels, ft_lstnew(new));
}

t_list	*get_bres_line(t_pixel p_0, t_pixel p_1)
{
	t_bres	bres;
	t_list	*pixels;

	bres = new_bres(p_0, p_1);
	pixels = NULL;
	while (true)
	{
		add_px_to_list(&pixels, p_0);
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
	return (pixels);
}
