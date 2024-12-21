/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfreyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 21:35/59 by kfreyer           #+#    #+#             */
/*   Updated: 2024/12/11 21:35:59 by kfreyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"
#include "mlx.h"
#include "my_mlx.h"
#include <X11/X.h>
#include <unistd.h>

void	setup_hooks(t_mlx_data mlx_data, t_projection p)
{
	void	*hook_params[2];

	hook_params[0] = (void *)&mlx_data;
	hook_params[1] = (void *)&p;
	mlx_hook(mlx_data.win_ptr, KeyPress, KeyPressMask, keypress_handler,
		&hook_params);
	mlx_hook(mlx_data.win_ptr, KeyRelease, KeyReleaseMask, keyrelease_hook,
		&hook_params);
	mlx_hook(mlx_data.win_ptr, ButtonPress, ButtonPressMask,
		button_press_handler, &hook_params);
	mlx_hook(mlx_data.win_ptr, ButtonRelease, ButtonReleaseMask,
		button_release_handler, &hook_params);
	mlx_hook(mlx_data.win_ptr, MotionNotify, Button1MotionMask,
		button1_motion_hook, &hook_params);
	mlx_hook(mlx_data.win_ptr, DestroyNotify, ButtonPressMask, destroy_hook,
		&hook_params);
	mlx_loop(mlx_data.mlx_ptr);
}

int	fdf(char *filename)
{
	t_projection	p;
	t_mlx_data		mlx_data;

	mlx_data.button1_pressed = false;
	mlx_data.mlx_ptr = mlx_init();
	mlx_data.size_x = 3840;
	mlx_data.size_y = 2160;
	if (!(mlx_data.mlx_ptr))
	{
		ft_putendl_fd("Error: Could not establish a connection", STDERR_FILENO);
		return (1);
	}
	mlx_data.win_ptr = mlx_new_window(mlx_data.mlx_ptr, mlx_data.size_x,
			mlx_data.size_y, "fdf");
	p = new_projection(filename, mlx_data.size_x, mlx_data.size_y);
	display_wf(p, mlx_data);
	setup_hooks(mlx_data, p);
	return (0);
}

int	main(int argc, char **argv)
{
	int	fd;

	if (argc != 2)
	{
		ft_putendl_fd("Error", STDERR_FILENO);
		return (1);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		ft_putendl_fd("Error", STDERR_FILENO);
		return (1);
	}
	close(fd);
	return (fdf(argv[1]));
}
