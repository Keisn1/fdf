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

# include "libft.h"
# include "my_mlx.h"

/* following algorithm: https://zingl.github.io/bresenham.html */
/* struct s_bres always relates to line between two points P0 = (x_0,
		y_0) and P1 = (x_1, y_1) */
typedef struct s_bres
{
	int	dx;
	int	sx;
	int	dy;
	int	sy;
	int	err;
	int	e2;
}		t_bresenham;

t_bresenham	new_bres(t_pixel p_0, t_pixel p_1);

typedef struct s_line {
	t_pixel pixels[2];
	int colors[2];
} t_line;

t_line	new_line(t_pixel px1, t_pixel px2, int col1, int col2);

void bres_plotline_simple(t_mlx_data mlx_data, t_img *img, t_line line, t_img_put_pixel_func t_img_put_pixel);
void	bres_plotline_window(t_mlx_data mlx_data, t_pixel p_0, t_pixel p_1, t_pixel_put_func pixel_put);
void	bres_plotline_img(t_mlx_data mlx_data, t_img *img, t_line line, t_img_put_pixel_func t_img_put_pixel);

void	bres_plotline_img_with_list(t_mlx_data mlx_data, t_img *img, t_line line, t_img_put_pixel_func img_put_pixel);
t_list	*get_bres_line(t_line line);

void	bres_plotline_img_template(t_mlx_data mlx_data, t_img *img, t_line line, t_img_put_pixel_func img_put_pixel);
unsigned int *get_gradient(unsigned int col1, unsigned int col2,
                           unsigned int steps);
/* helpers */
void				add_px_to_list(t_list **l, t_pixel p);

#endif // BRESENHAM_H
