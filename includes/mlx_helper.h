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

#ifndef MLX_HELPER_H
# define MLX_HELPER_H

typedef int			(*t_pixel_put_func)(void *, void *, int, int, int);

typedef struct s_point
{
	unsigned int	i;
	unsigned int	j;
}					t_point;

/* mlx */
typedef struct s_mlx_data
{
	void			*mlx_ptr;
	void			*win_ptr;
}					t_mlx_data;

int					my_mlx_pixel_put(void *mlx_ptr, void *win_ptr, int x, int y,
						int color);

#endif
