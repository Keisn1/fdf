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

enum
{
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_MOUSEDOWN = 4,
	ON_MOUSEUP = 5,
	ON_MOUSEMOVE = 6,
	ON_EXPOSE = 12,
	ON_DESTROY = 17
};

/* mlx */
typedef struct s_mlx_data
{
	void			*mlx_ptr;
	void			*win_ptr;
	t_list			*imgs;
}					t_mlx_data;

typedef struct s_pixel
{
	unsigned int	i;
	unsigned int	j;
}					t_pixel;

typedef struct s_img
{
	/* pointer to image in X-Server */
	void			*img;
	/* address of image data */
	char			*img_pixels;
	/* bits per pixel */
	int				bpp;
	int				size_line;
	int				endian;
	int				width;
	int				height;
}					t_img;

typedef int			(*t_pixel_put_func)(void *, void *, int, int, int);
typedef void		(*t_img_put_pixel_func)(void *, t_img *, t_pixel,
			unsigned int);

t_img				new_img(void *mlx_ptr, int width, int height);
t_pixel				new_pixel(double x, double y);
void				img_put_pixel(void *mlx_ptr, t_img *img, t_pixel px,
						unsigned int c);
void				destroy_imgs(t_list *imgs, void *mlx_ptr);

#endif
