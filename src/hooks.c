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
#include <stdio.h>

void	scale_up(t_projection *p)
{
	p->zoom++;
	scale_matrix(&p->projection, p->zoom_factor);
}

void	scale_down(t_projection *p)
{
	p->zoom--;
	scale_matrix(&p->projection, 1 / p->zoom_factor);
}

void	rotate_left(t_projection *p)
{
	t_matrix	rotation_z;
	t_matrix	rotated_vectors;

	p->rotation++;
	rotation_z = get_rot_matrix_z(p->rotation * p->drehwinkel);
	rotated_vectors = mat_mul(rotation_z, p->vectors);
	free_matrix(rotation_z);
	free_matrix(p->projection);
	p->projection = get_isometric_projection(rotated_vectors);
	free_matrix(rotated_vectors);
	scale_matrix(&p->projection, p->init_scale * pow(p->zoom_factor, p->zoom));
}

void	rotate_right(t_projection *p)
{
	t_matrix	rotation_z;
	t_matrix	rotated_vectors;

	p->rotation--;
	rotation_z = get_rot_matrix_z(p->rotation * p->drehwinkel);
	rotated_vectors = mat_mul(rotation_z, p->vectors);
	free_matrix(rotation_z);
	free_matrix(p->projection);
	p->projection = get_isometric_projection(rotated_vectors);
	free_matrix(rotated_vectors);
	scale_matrix(&p->projection, p->init_scale * pow(p->zoom_factor, p->zoom));
}

int mouse_up_hook(int button, int x, int y, void **params) {
	t_mlx_data		mlx_data;
	t_projection	*p;

	(void)button;
	(void)x;
	(void)y;
	mlx_data = *(t_mlx_data *)params[0];
	p = (t_projection *)params[1];
	printf("%d \n", button);
	if (button == 4)
		scale_up(p);
	if (button == 5)
		scale_down(p);
	display_wf(*p, mlx_data);
	return 0;
}

int	keypress_hook(int keycode, void **params)
{
	t_mlx_data		mlx_data;
	t_projection	*p;

	mlx_data = *(t_mlx_data *)params[0];
	p = (t_projection *)params[1];
	if (keycode == XK_Up)
		scale_up(p);
	if (keycode == XK_Down)
		scale_down(p);
	if (keycode == XK_Left)
		rotate_left(p);
	if (keycode == XK_Right)
		rotate_right(p);
	if (keycode == XK_l)
		translate_projection(&p->projection, 10, 0);
	if (keycode == XK_h)
		translate_projection(&p->projection, -10, 0);
	display_wf(*p, mlx_data);
	return (0);
}

int	keyrelease_hook(int keycode, void **params)
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

int	mouse_hook(int button, int x, int y, void *param)
{
	t_mlx_data	mlx_data;

	mlx_data = *(t_mlx_data *)param;
	if (button == 1)
		mlx_pixel_put(mlx_data.mlx_ptr, mlx_data.win_ptr, x, y, 0x008000FF);
	return (1);
}
