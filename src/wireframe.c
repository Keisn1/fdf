/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wireframe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfreyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 13:14/35 by kfreyer           #+#    #+#             */
/*   Updated: 2024/10/29 13:14:35 by kfreyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bresenham.h"
#include "fdf.h"
#include "my_mlx.h"
#include <unistd.h>

t_line	get_line_horizontal(t_projection p, int n, int m)
{
	int	idx;

	idx = n + (m * p.cols);
	return (new_line(new_pixel(p.projection.mat[0][idx], p.projection.mat[1][idx]),
			new_pixel(p.projection.mat[0][idx + 1], p.projection.mat[1][idx + 1]),
			p.colors[m][n], p.colors[m][n + 1]));
}

t_line	get_line_vertical(t_projection p, int n, int m, t_map map)
{
	int	idx;

	idx = n + (m * p.rows);
	return (new_line(new_pixel(p.projection .mat[0][idx], p.projection.mat[1][idx]),
			new_pixel(p.projection.mat[0][idx + p.rows], p.projection.mat[1][idx
				+ p.rows]), map.color[m][n], map.color[m + 1][n]));
}

void	wf_to_img_plot(t_mlx_data mlx_data, t_img img, t_projection p, t_map map)
{
	unsigned int	m;
	unsigned int	n;

	m = 0;
	while (m < p.rows)
	{
		n = 0;
		while (n < p.cols)
		{
			if (n < p.cols - 1)
				bres_plotline_img(mlx_data, &img, get_line_horizontal(p, n,
						m, map), img_put_pixel);
			if (m < p.rows - 1)
				bres_plotline_img(mlx_data, &img, get_line_vertical(p, n, m,
						map), img_put_pixel);
			n++;
		}
		m++;
	}
}

void display_wf(t_projection p, t_map map, t_mlx_data mlx_data) {
	t_img img;
	img = new_img(mlx_data.mlx_ptr, 1920, 1080);
	wf_to_img_plot(mlx_data, img, p, map);
	mlx_clear_window(mlx_data.mlx_ptr, mlx_data.win_ptr);
	mlx_put_image_to_window(mlx_data.mlx_ptr, mlx_data.win_ptr, img.img, 0, 0);
	mlx_destroy_image(mlx_data.mlx_ptr, img.img);
}
