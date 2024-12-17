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
#include <math.h>
#include <unistd.h>

int	main(int argc, char** argv)
{
	t_mlx_data	mlx_data;
	char		*filename;
	t_map		map;
	t_matrix	vectors;
	t_projection p;

	(void)argc;
	/* parse map */
	filename = argv[1];
	map = parse_map(filename);

	mlx_data.mlx_ptr = mlx_init();
	if (!(mlx_data.mlx_ptr))
	{
		ft_putendl_fd("Error: Could not establish a connection", STDERR_FILENO);
		return (1);
	}
	/* get a window */
	mlx_data.win_ptr = mlx_new_window(mlx_data.mlx_ptr, 1920, 1080, "wireframe");

	vectors = map_to_vectors(map);
	p.projection = get_isometric_projection(vectors);
	p.zoom_factor = 1.01;
	p.zoom = 0;
	p.drehwinkel = 5;
	p.rotation = 0;
	translate_vectors_to_first_octant(&p.projection);
	norm_vectors(&p.projection);
	scale_matrix(&p.projection, 900);
	scale_matrix(&p.projection, pow(p.zoom_factor, p.zoom));
	display_wf(p.projection, map, mlx_data);

	/* setup hooks */
	void* params_scale[4] = {(void*)&mlx_data, (void*)&p, (void*)&map, (void*)&vectors};
	mlx_hook(mlx_data.win_ptr, ON_KEYUP, 1L << 1, keyup_hook, &params_scale);
	mlx_loop(mlx_data.mlx_ptr);
	return (0);
}
