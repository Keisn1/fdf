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
# include <X11/X.h>
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
void				free_colors(unsigned int **colors, unsigned int rows);

enum				kind_p
{
	ISOMETRIC,
	PARALLEL
};

typedef struct s_projection
{
	enum kind_p		kind;
	t_matrix		vectors;
	t_matrix		projection;
	int				zoom;
	int				rotation;
	double			zoom_factor;
	double			drehwinkel;
	unsigned int	rows;
	unsigned int	cols;
	unsigned int	**colors;
	double			init_scale;
	int				translation_h;
	int				translation_v;
	int				last_pos_x;
	int				last_pos_y;
}					t_projection;

/* projection */
t_projection		new_projection(char *filename, double width, double height);
void	rebuild_projection(t_projection *p);
t_matrix			map_to_vectors(t_map map);
t_matrix			get_isometric_projection(t_matrix vectors);
t_matrix			get_parallel_projection(t_matrix vectors);
t_matrix			get_ip_matrix(void);
void				translate_vectors_to_first_octant(t_matrix *mat);
void				norm_vectors(t_matrix *mat);
void				display_wf(t_projection p, t_mlx_data mlx_data);

/* parsing */

/* hooks */
/* int					exit_program(int keycode, t_mlx_data *mlx_data); */
int					keyrelease_hook(int keycode, void **params);
int					keypress_handler(int keycode, void **params);
int					button_press_handler(int button, int x, int y,
						void **param);
int					button1_motion_hook(int x, int y, void **params);
int					button_release_handler(int button, int x, int y,
						void **params);

/* scaling */
void				scale_up(t_projection *p);
void				scale_down(t_projection *p);

/* rotation */
t_matrix			get_rot_matrix_z(double drehwinkel);
void				rotate_left(t_projection *p);
void				rotate_right(t_projection *p);

/* translation */
void				translate_projection(t_matrix *mat, int x, int y);
void				translate_left(t_projection *p);
void				translate_right(t_projection *p);
void				translate_up(t_projection *p);
void				translate_down(t_projection *p);

/* change projection */
void change_projection(t_projection *p);

/* helpers */
double				ft_abs_double(double x);

#endif // FDF_H
