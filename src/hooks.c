/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfreyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 15:26/22 by kfreyer           #+#    #+#             */
/*   Updated: 2024/12/12 15:26:22 by kfreyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx.h"
#include "my_mlx.h"


int	scale_hook(int keycode, t_mlx_data *mlx_data)
{
	if (keycode == XK_Up)
	{
		destroy_imgs(mlx_data->imgs, mlx_data->mlx_ptr);
		mlx_destroy_window(mlx_data->mlx_ptr, mlx_data->win_ptr);
		mlx_destroy_display(mlx_data->mlx_ptr);
		free(mlx_data->mlx_ptr);
		exit(0);
	}
	return (0);
}

int	mouse_hook(int button, int x, int y, void *param)
{
	t_mlx_data	mlx_data;

	mlx_data = *(t_mlx_data *)param;
	if (button == 1)
		mlx_pixel_put(mlx_data.mlx_ptr, mlx_data.win_ptr, x, y, 0x008000FF);
	return (1);
}

/* int	exit_program(int keycode, t_mlx_data *mlx_data) */
/* { */

/* 	if (keycode == XK_Escape) */
/* 	{ */
/* 		destroy_imgs(mlx_data->imgs, mlx_data->mlx_ptr); */
/* 		mlx_destroy_window(mlx_data->mlx_ptr, mlx_data->win_ptr); */
/* 		mlx_destroy_display(mlx_data->mlx_ptr); */
/* 		free(mlx_data->mlx_ptr); */
/* 		exit(0); */
/* 	} */
/* 	return (0); */
/* } */

int	exit_program(int keycode, void** params)
{
	t_mlx_data *mlx_data = (t_mlx_data*)params[0];
	t_matrix *isometric_projection = (t_matrix*)params[1];
	t_map *map = (t_map*)params[2];

	free_map(*map);
	free_matrix(*isometric_projection);

	if (keycode == XK_Escape)
	{
		destroy_imgs(mlx_data->imgs, mlx_data->mlx_ptr);
		mlx_destroy_window(mlx_data->mlx_ptr, mlx_data->win_ptr);
		mlx_destroy_display(mlx_data->mlx_ptr);
		free(mlx_data->mlx_ptr);
		exit(0);
	}
	return (0);
}
