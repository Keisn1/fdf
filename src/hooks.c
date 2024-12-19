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
#include <X11/X.h>
#include <math.h>
#include <stdio.h>

void	scale_up(t_projection *p)
{
	p->zoom++;
	scale_matrix(&p->projection, p->zoom_factor);
	p->translation_h = p->translation_h * p->zoom_factor;
	p->translation_v = p->translation_v * p->zoom_factor;
}

void	scale_down(t_projection *p)
{
	p->zoom--;
	scale_matrix(&p->projection, 1 / p->zoom_factor);
	p->translation_h = p->translation_h / p->zoom_factor;
	p->translation_v = p->translation_v / p->zoom_factor;
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
	p->projection = get_parallel_projection(rotated_vectors);
	free_matrix(rotated_vectors);
	scale_matrix(&p->projection, p->init_scale * pow(p->zoom_factor, p->zoom));
	translate_projection(&p->projection, p->translation_h , p->translation_v );
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
	p->projection = get_parallel_projection(rotated_vectors);
	free_matrix(rotated_vectors);
	scale_matrix(&p->projection, p->init_scale * pow(p->zoom_factor, p->zoom));
	translate_projection(&p->projection, p->translation_h , p->translation_v );
}

int	button_press_hook(int button, int x, int y, void **params)
{
	t_mlx_data		*mlx_data;
	t_projection	*p;

	(void)x;
	(void)y;
	mlx_data = (t_mlx_data *)params[0];
	p = (t_projection *)params[1];

	if (button == Button1)
		mlx_data->button1_pressed = true;
	if (button == Button4)
		scale_up(p);
	if (button == Button5)
		scale_down(p);
	display_wf(*p, *mlx_data);
	return (0);
}

void	translate_left(t_projection *p)
{
	p->translation_h--;
	translate_projection(&p->projection, -1, 0);
}
void	translate_right(t_projection *p)
{
	p->translation_h++;
	translate_projection(&p->projection, 1, 0);
}
void	translate_up(t_projection *p)
{
	p->translation_v--;
	translate_projection(&p->projection, 0, -1);
}
void	translate_down(t_projection *p)
{
	p->translation_v++;
	translate_projection(&p->projection, 0, 1);
}

int	keypress_hook(int keycode, void **params)
{
	t_mlx_data		mlx_data;
	t_projection	*p;

	mlx_data = *(t_mlx_data *)params[0];
	p = (t_projection *)params[1];
	if (keycode == XK_u)
		rotate_left(p);
	if (keycode == XK_i)
		rotate_right(p);
	if (keycode == XK_Left)
		translate_left(p);
	if (keycode == XK_Right)
		translate_right(p);
	if (keycode == XK_Up)
		translate_up(p);
	if (keycode == XK_Down)
		translate_down(p);
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

int button1_motion_hook(int x, int y, void **params) {
	t_mlx_data		*mlx_data;
	t_projection	*p;

	mlx_data = (t_mlx_data *)params[0];
	p = (t_projection *)params[1];
	if (mlx_data->button1_pressed) {
		if (p->last_pos_x == 0 && p->last_pos_y == 0) {
			p->last_pos_x = x;
			p->last_pos_y = y;
			return 0;
		}
		int delta_x = x - p->last_pos_x;
		int delta_y = y - p->last_pos_y;
		p->last_pos_x = x;
		p->last_pos_y = y;

		p->translation_h += delta_x;
		p->translation_v += delta_y;
		translate_projection(&p->projection, delta_x, delta_y);
		display_wf(*p, *mlx_data);
	}
	return 0;
}

int button_release_hook(int button, int x, int y, void **params) {
	t_projection	*p;
	(void)x;
	(void)y;

	t_mlx_data		*mlx_data;
	mlx_data = (t_mlx_data *)params[0];
	p = (t_projection *)params[1];

	if (button == Button1) {
		p->last_pos_x = 0;
		p->last_pos_y = 0;
		mlx_data->button1_pressed = false;
	}
	return (0);
}
