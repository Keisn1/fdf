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

void translate_matrix(t_matrix *m, double x, double y) {
	unsigned int c2;
	c2 = 0;
	while (c2 < m->n)
	{
		m->mat[0][c2] += x;
		m->mat[1][c2] += y;
		c2++;
	}
}

double get_max(t_extrema extrema) {
	if (extrema.max_x < extrema.max_y)
		return extrema.max_y;
	return extrema.max_x;
}

void norm_matrix(t_matrix *m, t_extrema extrema) {
	double max = get_max(extrema);
	unsigned int i;
	unsigned int j;

	i = 0;
	while (i < m->m) {
		j = 0;
		while (j < m->n) {
			m->mat[i][j] /= max;
			j++;
		}
		i++;
	}
}

void scale_matrix(t_matrix *m, double scale) {
	unsigned int i;
	unsigned int j;

	i = 0;
	while (i < m->m) {
		j = 0;
		while (j < m->n) {
			m->mat[i][j] *= scale;
			j++;
		}
		i++;
	}
}

int	main(int argc, char** argv)
{
	t_mlx_data	mlx_data;
	char		*filename;
	t_map		map;
	t_matrix	isometric_projection;
	t_extrema	extrema;
	double		x_translation;
	double		y_translation;
	size_t		size_win_x;
	size_t		size_win_y;
	t_img		img;

	(void)argc;
	/* parse map */
	filename = argv[1];
	map = parse_map(filename);
	isometric_projection = get_isometric_projection(map);

	/* translatation by minimum */
	extrema = get_extrema(isometric_projection);

	x_translation = extrema.min_x;
	y_translation = extrema.min_y;

	translate_matrix(&isometric_projection, -extrema.min_x, -extrema.min_y);

	extrema.min_x -= x_translation;
	extrema.max_x -= x_translation;
	extrema.min_y -= y_translation;
	extrema.max_y -= y_translation;

	size_win_x = 3840;
	size_win_y = 2160;
	norm_matrix(&isometric_projection, extrema);
	scale_matrix(&isometric_projection, size_win_y);


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
