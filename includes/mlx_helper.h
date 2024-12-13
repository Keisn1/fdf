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

# include "libft.h"
/* mlx */
typedef struct s_mlx_data
{
	void			*mlx_ptr;
	void			*win_ptr;
	t_list			*imgs;
}					t_mlx_data;

typedef int			(*t_pixel_put_func)(void *, void *, int, int, int);

typedef struct s_pixel
{
	unsigned int	i;
	unsigned int	j;
}					t_pixel;

#endif
