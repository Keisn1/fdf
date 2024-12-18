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
#include "matrix.h"
#include "my_mlx.h"
#include <math.h>

int	keyup_hook(int keycode, void** params)
{
	t_mlx_data mlx_data = *(t_mlx_data*)params[0];
	t_projection *p = (t_projection*)params[1];
	t_map map = *(t_map*)params[2];

	if (keycode == XK_Up) {
		p->zoom++;
		scale_matrix(&p->projection, p->zoom_factor);
		display_wf(*p,  mlx_data);
	}
	if (keycode == XK_Down) {
		p->zoom--;
		scale_matrix(&p->projection, 1 / p->zoom_factor);
		display_wf(*p,  mlx_data);
	}
	if (keycode == XK_Left) {
		p->rotation++;
		t_matrix rotation_z = get_rot_matrix_z(p->rotation * p->drehwinkel);
		t_matrix rotated_vectors = mat_mul(rotation_z, p->vectors);
		free_matrix(rotation_z);

		free_matrix(p->projection);
		p->projection = get_isometric_projection(rotated_vectors);
		free_matrix(rotated_vectors);

		scale_matrix(&p->projection, pow(p->zoom_factor, p->zoom));
		display_wf(*p,  mlx_data);
	}

	if (keycode == XK_Escape)
	{
		free_map(map);
		free_matrix(p->projection);
		free_matrix(p->vectors);
		mlx_destroy_window(mlx_data.mlx_ptr, mlx_data.win_ptr);
		mlx_destroy_display(mlx_data.mlx_ptr);
		free(mlx_data.mlx_ptr);
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

