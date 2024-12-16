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

#include "my_mlx.h"
#include <math.h>

t_pixel	new_pixel(double x, double y)
{
	return ((t_pixel){(int)round(x), (int)round(y)});
}

/* bpp/8 gives you the number of bytes you need to jump,
	to jump a whole pixel */
void	img_put_pixel(void *mlx_ptr, t_img *img, t_pixel px, unsigned int c)
{
	int	offset;

	if ((int)px.y >= img->height || (int)px.x >= img->width)
		return;
	offset = px.y * img->size_line + px.x * (img->bpp / 8);
	*(unsigned int *)(img->img_pixels + offset) = mlx_get_color_value(mlx_ptr,
			c);
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

void	destroy_imgs(t_list *imgs, void *mlx_ptr)
{
	t_list	*head;
	t_list	*tmp;

	head = imgs;
	tmp = NULL;
	while (head)
	{
		mlx_destroy_image(mlx_ptr, ((t_img *)head->content)->img);
		tmp = head;
		head = head->next;
		free(tmp);
	}
}
