/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfreyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 17:17/48 by kfreyer           #+#    #+#             */
/*   Updated: 2024/12/13 17:17:48 by kfreyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx.h"

/* bpp/8 gives you the number of bytes you need to jump,
	to jump a whole pixel */
void	img_put_pixel(void *mlx_ptr, t_img *img, t_pixel pos,
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
