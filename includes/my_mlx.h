/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfreyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 17:00/48 by kfreyer           #+#    #+#             */
/*   Updated: 2024/11/28 17:00:48 by kfreyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MY_MLX_H
# define MY_MLX_H

# include "libft.h"
# include "mlx.h"

/* mlx */
typedef struct s_mlx_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	bool	button1_pressed;
	int		size_x;
	int		size_y;

}			t_mlx_data;

typedef struct s_pixel
{
	int		x;
	int		y;
}			t_pixel;

typedef struct s_img
{
	/* pointer to image in X-Server */
	void	*img;
	/* address of image data */
	char	*img_pixels;
	/* bits per pixel */
	int		bpp;
	/* number of bytes used to store one line of the image in memory */
	int		size_line;
	int		endian;
	int		width;
	int		height;
}			t_img;

typedef int	(*t_pixel_put_func)(void *, void *, int, int, int);

t_img		new_img(void *mlx_ptr, int width, int height);
t_pixel		new_pixel(double x, double y);
void		img_put_pixel(void *mlx_ptr, t_img *img, t_pixel px,
				unsigned int c);
void		destroy_imgs(t_list *imgs, void *mlx_ptr);

#endif
