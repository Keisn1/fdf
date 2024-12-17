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

int	main(int argc, char** argv)
{
	t_mlx_data	mlx_data;
	char		*filename;
	t_map		map;
	t_matrix	vectors;
	size_t		size_win_x;
	size_t		size_win_y;
	t_projection p;

	(void)argc;
	/* parse map */
	filename = argv[1];
	map = parse_map(filename);
	vectors = map_to_vectors(map);
	p.projection = get_isometric_projection(vectors);
	/* isometric_projection = get_isometric_projection(vectors); */
	translate_vectors_to_first_octant(&p.projection);
	/* translate_vectors_to_first_octant(&isometric_projection); */
	norm_vectors(&p.projection);
	/* norm_vectors(&isometric_projection); */

	size_win_x = 1920;
	size_win_y = 1080;
	double scale_factor = size_win_x;
	if (size_win_y < size_win_x)
		scale_factor = size_win_y;


	mlx_data.mlx_ptr = mlx_init();
	if (!(mlx_data.mlx_ptr))
	{
		ft_putendl_fd("Error: Could not establish a connection", STDERR_FILENO);
		return (1);
	}
	/* get a window */
	mlx_data.win_ptr = mlx_new_window(mlx_data.mlx_ptr, size_win_x, size_win_y, "wireframe");
	display_wf(p.projection, map, mlx_data, scale_factor);
	/* display_wf(isometric_projection, map, mlx_data, scale_factor); */

	/* setup hooks */
	void* params_scale[4] = {(void*)&mlx_data, (void*)&p, (void*)&map, (void*)&vectors};
	mlx_hook(mlx_data.win_ptr, ON_KEYUP, 1L << 1, keyup_hook, &params_scale);
	mlx_loop(mlx_data.mlx_ptr);
	return (0);
}
