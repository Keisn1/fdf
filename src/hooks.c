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


int	keyup_hook(int keycode, void** params)
{
	t_img		img;
	t_mlx_data mlx_data = *(t_mlx_data*)params[0];
	t_matrix isometric_projection = *(t_matrix*)params[1];
	t_map map = *(t_map*)params[2];

	if (keycode == XK_Up)
	{
		scale_matrix(&isometric_projection, 1.03);
		img = new_img(mlx_data.mlx_ptr, 960, 540);
		wf_to_img_plot(mlx_data, img, isometric_projection, map);

		/* t_img *cur_img = (t_img*)(mlx_data.imgs->content); */
		/* mlx_destroy_image(mlx_data.mlx_ptr, cur_img->img); */

		mlx_put_image_to_window(mlx_data.mlx_ptr, mlx_data.win_ptr, img.img, 200, 200);
	}

	if (keycode == XK_Escape)
	{
		free_map(map);
		free_matrix(isometric_projection);
		destroy_imgs(mlx_data.imgs, mlx_data.mlx_ptr);
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

