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
#include <unistd.h>

int	main(int argc, char **argv)
{
	t_mlx_data		mlx_data;
	t_projection	p;
	void			*hook_params[2] = {(void *)&mlx_data, (void *)&p};

	(void)argc;
	mlx_data.mlx_ptr = mlx_init();
	if (!(mlx_data.mlx_ptr))
	{
		ft_putendl_fd("Error: Could not establish a connection", STDERR_FILENO);
		return (1);
	}
	/* get a window */
	mlx_data.win_ptr = mlx_new_window(mlx_data.mlx_ptr, 1920, 1080, "fdf");
	p = new_projection(argv[1]);
	display_wf(p, mlx_data);
	/* setup hooks */
	mlx_hook(mlx_data.win_ptr, ON_KEYUP, 1L << 1, keyup_hook, &hook_params);
	mlx_loop(mlx_data.mlx_ptr);
	return (0);
}
