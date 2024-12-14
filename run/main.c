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
#include <unistd.h>

int	main(int argc, char** argv)
{
	t_mlx_data	mlx_data;
	char		*filename;
	t_map		map;
	t_matrix	isometric_projection;
	size_t		size_win_x;
	size_t		size_win_y;
	t_img		img;

	(void)argc;
	/* parse map */
	filename = argv[1];
	map = parse_map(filename);
	isometric_projection = get_isometric_projection(map);
	translate_vectors_to_first_octant(&isometric_projection);
	norm_vectors(&isometric_projection);

	size_win_x = 3840;
	size_win_y = 2160;
	double scale_factor = size_win_x;
	if (size_win_y < size_win_x)
		scale_factor = size_win_y;
	scale_matrix(&isometric_projection, scale_factor);

	mlx_data.mlx_ptr = mlx_init();
	if (!(mlx_data.mlx_ptr))
	{
		ft_putendl_fd("Error: Could not establish a connection", STDERR_FILENO);
		return (1);
	}

	/* create the image */
	img = new_img(mlx_data.mlx_ptr, size_win_x, size_win_y);
	mlx_data.imgs = ft_lstnew(&img);

	/* put the wireframe to image */
	wf_to_img_plot(mlx_data, img, isometric_projection, map);

	/* free all the stuff */
	free_map(map);
	free_matrix(isometric_projection);

	mlx_data.win_ptr = mlx_new_window(mlx_data.mlx_ptr, size_win_x, size_win_y, "wireframe");
	mlx_put_image_to_window(mlx_data.mlx_ptr, mlx_data.win_ptr, img.img, 0, 0);

	/* put image to window */
	mlx_hook(mlx_data.win_ptr, ON_KEYUP, 1L << 1, exit_program, &mlx_data);
	mlx_loop(mlx_data.mlx_ptr);
	return (0);
}
