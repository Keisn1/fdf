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
#include "mlx.h"
#include "my_mlx.h"

int	keyup_hook(int keycode, void** params)
{
	t_mlx_data mlx_data = *(t_mlx_data*)params[0];
	t_projection *p = (t_projection*)params[1];
	t_map map = *(t_map*)params[2];
	t_matrix vectors = *(t_matrix*)params[3];

	if (keycode == XK_Up)
		display_wf(p->projection, map, mlx_data, 1.03);
	if (keycode == XK_Down)
		display_wf(p->projection, map, mlx_data, 0.97);
	if (keycode == XK_Left) {
		t_matrix rotation_z = get_rot_matrix_z();
		t_matrix new_vectors = mat_mul(rotation_z, vectors);
		free_matrix(rotation_z);

		t_matrix rot_matrix = get_rot_matrix();

		free_matrix(p->projection);
		p->projection = mat_mul(rot_matrix, new_vectors);
		free_matrix(new_vectors);
		free_matrix(rot_matrix);

		translate_vectors_to_first_octant(&(p->projection));
		norm_vectors(&(p->projection));
		display_wf(p->projection, map, mlx_data, 1080);
	}

	if (keycode == XK_Escape)
	{
		free_map(map);
		free_matrix(p->projection);
		free_matrix(vectors);
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

