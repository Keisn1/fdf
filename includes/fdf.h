/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfreyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 16:35/19 by kfreyer           #+#    #+#             */
/*   Updated: 2024/11/28 16:35:19 by kfreyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "libft.h"
# include "matrix.h"
# include "my_mlx.h"
# include <X11/keysym.h>
# include <limits.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

/* hooks */
int					exit_program(int keycode, t_mlx_data *mlx_data);

t_matrix			get_rot_matrix(void);
t_list				*get_wireframe_indices(size_t wf_m, size_t wf_n);

/* parsing */
typedef struct s_map
{
	t_matrix		map;
	unsigned int	**color;
}					t_map;

t_map				parse_map(const char *filename);
void				free_map(t_map map);
t_matrix			map_to_vectors(t_map map);

typedef struct s_extrema
{
	double			min_x;
	double			min_y;
	double			max_x;
	double			max_y;
}					t_extrema;
t_extrema			get_extrema(t_matrix M);

t_matrix			get_isometric_projection(t_map map);
void				translate_vectors(t_matrix *m, double x, double y);
void				wf_to_img(t_mlx_data mlx_data, t_img img, t_matrix M,
						t_map map);

#endif // FDF_H
