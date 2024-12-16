/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfreyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 16:58/45 by kfreyer           #+#    #+#             */
/*   Updated: 2024/11/28 16:58:45 by kfreyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BRESENHAM_H
# define BRESENHAM_H

# include "my_mlx.h"

/* following algorithm: https://zingl.github.io/bresenham.html */
/* struct s_bres always relates to line between two points P0 = (x_0,
		y_0) and P1 = (x_1, y_1) */
typedef struct s_bres
{
	int			dx;
	int			sx;
	int			dy;
	int			sy;
	int			err;
	int			e2;
}				t_bresenham;

t_bresenham		new_bres(t_pixel p_0, t_pixel p_1);

typedef struct s_line
{
	t_pixel		pixels[2];
	int			colors[2];
}				t_line;

t_line			new_line(t_pixel px1, t_pixel px2, int col1, int col2);

typedef void	(*t_img_put_pixel_func)(void *, t_img *, t_pixel, unsigned int);

void			extract_rgb(int color, float rgb[3]);
void			fill_grad_step(float grad_step[3], t_line line, int steps);
int				add_g_step(float color[3], float grad_step[3]);
void			bres_plotline_img(t_mlx_data mlx_data, t_img *img, t_line line,
					t_img_put_pixel_func ipp);

#endif // BRESENHAM_H
