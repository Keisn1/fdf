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

# include "matrix.h"
# include "my_mlx.h"
# include <X11/keysym.h>
# include <fcntl.h>
# include <limits.h>
# include <stdbool.h>
# include <stddef.h>
# include <unistd.h>

typedef struct s_map
{
	t_matrix		map;
	unsigned int	**color;
}					t_map;

void				free_map(t_map map);
char				*advance_to_comma_or_ws(char *str);
t_matrix			map_to_vectors(t_map map);
unsigned int		ft_hex_to_unsigned(char *hex_str);
t_map				parse_map(const char *filename);


typedef struct s_projection {
	t_matrix vectors;
	t_matrix projection;
	int zoom;
	int rotation;
	double zoom_factor;
	double drehwinkel;
	unsigned int rows;
	unsigned int cols;
} t_projection;


/* projection */
t_projection new_projection(t_map map);
t_matrix	get_isometric_projection(t_matrix vectors);
t_matrix	get_rot_matrix(void);
t_matrix	get_rot_matrix_z(double drehwinkel);
void				translate_vectors_to_first_octant(t_matrix *mat);
void				norm_vectors(t_matrix *mat);
void display_wf(t_projection p, t_map map, t_mlx_data mlx_data);

/* parsing */
void				translate_vectors(t_matrix *m, double x, double y);
void				wf_to_img_plot(t_mlx_data mlx_data, t_img img, t_matrix M,
						t_map map);

/* hooks */
/* int					exit_program(int keycode, t_mlx_data *mlx_data); */
int	keyup_hook(int keycode, void** params);
#endif // FDF_H
