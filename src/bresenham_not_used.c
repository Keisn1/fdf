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
	t_bresenham	bres;
	t_list		*pixels;

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

void	bres_plotline_img_with_list(t_mlx_data mlx_data, t_pixel p_0,
		t_pixel p_1, t_img *img)
{
	t_list	*line;
	t_list	*head;

	line = get_bres_line(p_0, p_1);
	head = line;
	while (head)
	{
		img_put_pixel(mlx_data.mlx_ptr, img, *(t_pixel *)head->content,
			0xFF00FF);
		head = head->next;
	}
	ft_lstclear(&line, free);
}

void	bres_plotline_window(t_mlx_data mlx_data, t_pixel p_0, t_pixel p_1,
		t_pixel_put_func pixel_put)
{
	t_bresenham	bres;

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
