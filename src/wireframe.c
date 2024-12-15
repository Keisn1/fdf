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

t_line	get_line_horizontal(t_matrix vectors, size_t idx)
{
	return (new_line(new_pixel(vectors.mat[0][idx], vectors.mat[1][idx]),
			new_pixel(vectors.mat[0][idx + 1], vectors.mat[1][idx + 1])));
}

t_line	get_line_vertical(t_matrix vectors, size_t idx, unsigned int len_row)
{
	return (new_line(new_pixel(vectors.mat[0][idx], vectors.mat[1][idx]),
			new_pixel(vectors.mat[0][idx + len_row], vectors.mat[1][idx
				+ len_row])));
}

void	wf_to_img_plot(t_mlx_data mlx_data, t_img img, t_matrix vectors,
		t_map map)
{
	unsigned int	count_m;
	unsigned int	count_n;
	size_t			idx;

	count_m = 0;
	idx = 0;
	while (count_m < map.map.m)
	{
		count_n = 0;
		while (count_n < map.map.n)
		{
			if (count_n < map.map.n - 1)
				bres_plotline_img(mlx_data, &img, get_line_horizontal(vectors,
						idx), img_put_pixel);
			if (count_m < map.map.m - 1)
				bres_plotline_img(mlx_data, &img, get_line_vertical(vectors,
						idx, map.map.n), img_put_pixel);
			count_n++;
			idx++;
		}
		count_m++;
	}
}
