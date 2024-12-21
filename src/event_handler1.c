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
#include "my_mlx.h"

int	button_press_handler(int button, int x, int y, void **params)
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

int	button_release_handler(int button, int x, int y, void **params)
{
	t_projection	*p;
	t_mlx_data		*mlx_data;

	(void)x;
	(void)y;
	mlx_data = (t_mlx_data *)params[0];
	p = (t_projection *)params[1];
	if (button == Button1)
	{
		p->last_pos_x = 0;
		p->last_pos_y = 0;
		mlx_data->button1_pressed = false;
	}
	return (0);
}

int	button1_motion_hook(int x, int y, void **params)
{
	t_mlx_data		*mlx_data;
	t_projection	*p;
	int				delta_x;
	int				delta_y;

	mlx_data = (t_mlx_data *)params[0];
	p = (t_projection *)params[1];
	if (mlx_data->button1_pressed)
	{
		if (p->last_pos_x == 0 && p->last_pos_y == 0)
		{
			p->last_pos_x = x;
			p->last_pos_y = y;
			return (0);
		}
		delta_x = x - p->last_pos_x;
		delta_y = y - p->last_pos_y;
		p->last_pos_x = x;
		p->last_pos_y = y;
		p->translation_h += delta_x;
		p->translation_v += delta_y;
		translate_projection(&p->projection, delta_x, delta_y);
		display_wf(*p, *mlx_data);
	}
	return (0);
}

int	keypress_handler(int keycode, void **params)
{
	t_mlx_data		mlx_data;
	t_projection	*p;

	mlx_data = *(t_mlx_data *)params[0];
	p = (t_projection *)params[1];
	if (keycode == XK_p)
		change_projection(p);
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
