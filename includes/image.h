/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfreyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 17:21/52 by kfreyer           #+#    #+#             */
/*   Updated: 2024/12/13 17:21:52 by kfreyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef IMAGE_H
# define IMAGE_H

# include "mlx_helper.h"

typedef struct s_img
{
	void *img;        /* pointer to image in X-Server */
	char *img_pixels; /* address of image data */
	int bpp;          /* bits per pixel */
	int	size_line;
	int	endian;
	int	width;
	int	height;
}		t_img;

t_img	new_img(void *mlx_ptr, int width, int height);
void	img_put_pixel(void *mlx_ptr, t_img *img, t_pixel pos,
			unsigned int color);

#endif // IMAGE_H
