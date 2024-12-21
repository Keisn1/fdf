/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handler2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfreyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 10:18/49 by kfreyer           #+#    #+#             */
/*   Updated: 2024/12/21 10:18:49 by kfreyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "matrix.h"
#include "my_mlx.h"

int	keyrelease_handler(int keycode, void **params)
{
	t_mlx_data		mlx_data;
	t_projection	*p;

	mlx_data = *(t_mlx_data *)params[0];
	p = (t_projection *)params[1];
	if (keycode == XK_Escape)
	{
		free_matrix(p->projection);
		free_matrix(p->vectors);
		free_colors(p->colors, p->rows);
		mlx_destroy_window(mlx_data.mlx_ptr, mlx_data.win_ptr);
		mlx_destroy_display(mlx_data.mlx_ptr);
		free(mlx_data.mlx_ptr);
		exit(0);
	}
	return (0);
}

int	destroy_handler(void **params)
{
	t_mlx_data		mlx_data;
	t_projection	*p;

	mlx_data = *(t_mlx_data *)params[0];
	p = (t_projection *)params[1];
	free_matrix(p->projection);
	free_matrix(p->vectors);
	free_colors(p->colors, p->rows);
	mlx_destroy_window(mlx_data.mlx_ptr, mlx_data.win_ptr);
	mlx_destroy_display(mlx_data.mlx_ptr);
	free(mlx_data.mlx_ptr);
	exit(0);
	return (0);
}
