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
	unsigned int	**colors;
}					t_map;

t_map				parse_map(const char *filename);
char				*advance_to_comma_or_ws(char *str);
unsigned int		ft_hex_to_unsigned(char *hex_str);
void	free_colors(unsigned int** colors, unsigned int rows);


typedef struct s_projection {
	t_matrix vectors;
	t_matrix projection;
	int zoom;
	int rotation;
	double zoom_factor;
	double drehwinkel;
	unsigned int rows;
	unsigned int cols;
	unsigned int** colors;
	double init_scale;
} t_projection;


/* projection */
t_projection	new_projection(char *filename, double width, double height);
t_matrix			map_to_vectors(t_map map);
t_matrix	get_isometric_projection(t_matrix vectors);
t_matrix	get_rot_matrix(void);
t_matrix	get_rot_matrix_z(double drehwinkel);
void				translate_vectors_to_first_octant(t_matrix *mat);
void				norm_vectors(t_matrix *mat);
void display_wf(t_projection p, t_mlx_data mlx_data);
void	translate_projection(t_matrix *mat, double x, double y);

/* parsing */
void				translate_projection(t_matrix *m, double x, double y);

/* hooks */
/* int					exit_program(int keycode, t_mlx_data *mlx_data); */
int	keyrelease_hook(int keycode, void** params);
int keypress_hook(int keycode, void **params);
int mouse_up_hook(int button, int x, int y, void **param);
#endif // FDF_H
