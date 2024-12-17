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

t_line	get_line_horizontal(t_matrix vectors, int n, int m, t_map map)
{
	int	idx;

	idx = n + (m * map.map.n);
	return (new_line(new_pixel(vectors.mat[0][idx], vectors.mat[1][idx]),
			new_pixel(vectors.mat[0][idx + 1], vectors.mat[1][idx + 1]),
			map.color[m][n], map.color[m][n + 1]));
}

t_line	get_line_vertical(t_matrix vectors, int n, int m, t_map map)
{
	int	idx;

	idx = n + (m * map.map.n);
	return (new_line(new_pixel(vectors.mat[0][idx], vectors.mat[1][idx]),
			new_pixel(vectors.mat[0][idx + map.map.n], vectors.mat[1][idx
				+ map.map.n]), map.color[m][n], map.color[m + 1][n]));
}

void	wf_to_img_plot(t_mlx_data mlx_data, t_img img, t_matrix vecs, t_map map)
{
	unsigned int	m;
	unsigned int	n;

	m = 0;
	while (m < map.map.m)
	{
		n = 0;
		while (n < map.map.n)
		{
			if (n < map.map.n - 1)
				bres_plotline_img(mlx_data, &img, get_line_horizontal(vecs, n,
						m, map), img_put_pixel);
			if (m < map.map.m - 1)
				bres_plotline_img(mlx_data, &img, get_line_vertical(vecs, n, m,
						map), img_put_pixel);
			n++;
		}
		m++;
	}
}

void display_wf(t_matrix isometric_projection, t_map map, t_mlx_data mlx_data, double scale) {
	t_img img;
	scale_matrix(&isometric_projection, scale);
	img = new_img(mlx_data.mlx_ptr, 1920, 1080);
	wf_to_img_plot(mlx_data, img, isometric_projection, map);
	mlx_clear_window(mlx_data.mlx_ptr, mlx_data.win_ptr);
	mlx_put_image_to_window(mlx_data.mlx_ptr, mlx_data.win_ptr, img.img, 0, 0);
	mlx_destroy_image(mlx_data.mlx_ptr, img.img);
}
