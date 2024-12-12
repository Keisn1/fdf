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
# include "mlx_helper.h"

/* following algorithm: https://zingl.github.io/bresenham.html */
/* struct s_bres always relates to line between two points P0 = (x_0, y_0) and P1 = (x_1, y_1) */
typedef struct	s_bres
{
	int	dx;
	int	sx;
	int	dy;
	int	sy;
	int	err;
	int	e2;
} t_bres;

void	bres_plotline(t_mlx_data mlx_data, t_point p_0, t_point p_1,
			t_pixel_put_func pixel_put);
t_list	*get_bres_line(t_point p_0, t_point p_1);

#endif // BRESENHAM_H
