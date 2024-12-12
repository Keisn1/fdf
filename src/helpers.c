/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   by: kfreyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   created: 2024/12/12 22:48/53 by kfreyer           #+#    #+#             */
/*   updated: 2024/12/12 22:48:53 by kfreyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx.h"
#include <stdlib.h>

/* just a thought about UI testing  */
/* a test would set up data and checks for right values in data after calling img_put_pixel */
/* to create my test_data, i would also use mlx_get_color_value  */
/* bpp/8 gives you the number of bytes you need to jump,
	to jump a whole pixel */
void	img_put_pixel(void *mlx_ptr, t_img *img, t_point pos,
		unsigned int color)
{
	int	offset;

	offset = pos.j * img->size_line + pos.i * (img->bpp / 8);
	*(unsigned int *)(img->img_pixels + offset) = mlx_get_color_value(mlx_ptr,
			color);
}

t_img	new_img(void *mlx_ptr, int width, int height)
{
	t_img	img;

	img.img = mlx_new_image(mlx_ptr, width, height);
	img.img_pixels = mlx_get_data_addr(img.img, &img.bpp, &img.size_line,
			&img.endian);
	img.width = width;
	img.height = height;
	return (img);
}

int	my_mlx_pixel_put(void *mlx_ptr, void *win_ptr, int x, int y, int color)
{
	return (mlx_pixel_put(mlx_ptr, win_ptr, x, y, color));
}

void	free_matrix(t_matrix M)
{
	int	m_count;

	m_count = 0;
	while (m_count < M.m)
		free(M.mat[m_count++]);
	free(M.mat);
}
