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


int	main(void)
{
	t_mlx_data	mlx_data;
	char		*filename;
	t_map		map;
	t_matrix	vectors;
	t_matrix	mat_isometric_projection;
	t_matrix	isometric_projection;
	t_limits	limits;
	double		x_translation;
	double		y_translation;
	size_t		size_win_x;
	size_t		size_win_y;
	double		scale;
	unsigned int			c1;
	unsigned int			c2;
	t_img		img;


	/* parse map */
	filename = "test_maps/42.fdf";
	map = parse_map(filename);

	/* map -> matrix */
	vectors = map_to_vectors(map);
	/* calculate isometric projection matrix */
	mat_isometric_projection = get_rot_matrix();
	isometric_projection = mat_mul(mat_isometric_projection, vectors);

	free_matrix(vectors);
	free_matrix(mat_isometric_projection);

	/* translatation by minimum */
	limits = get_limits(isometric_projection);
	x_translation = limits.min_x;
	y_translation = limits.min_y;

	c2 = 0;
	while (c2 < isometric_projection.n)
	{
		isometric_projection.mat[0][c2] -= x_translation;
		isometric_projection.mat[1][c2] -= y_translation;
		c2++;
	}
	limits.min_x -= x_translation;
	limits.max_x -= x_translation;
	limits.min_y -= y_translation;
	limits.max_y -= y_translation;

	/* scaling to window size */
	size_win_x = 480;
	size_win_y = 270;
	scale = get_scale(size_win_x, size_win_y, limits);
	c1 = 0;
	while (c1 < isometric_projection.m)
	{
		c2 = 0;
		while (c2 < isometric_projection.n)
		{
			isometric_projection.mat[c1][c2] *= scale;
			c2++;
		}
		c1++;
	}

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
	wf_to_img(mlx_data, img, isometric_projection, map);

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
