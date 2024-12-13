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

# include "image.h"
# include "libft.h"
# include "matrix.h"
# include "mlx_helper.h"
# include <X11/keysym.h>
# include <limits.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

int					exit_program(int keycode, t_mlx_data *mlx_data);

enum
{
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_MOUSEDOWN = 4,
	ON_MOUSEUP = 5,
	ON_MOUSEMOVE = 6,
	ON_EXPOSE = 12,
	ON_DESTROY = 17
};

t_matrix			get_rot_matrix(void);
t_list				*get_wireframe_indices(size_t wf_m, size_t wf_n);

/* helpers */
void				add_back_point(t_list **l, t_pixel p);
void				print_matrix(double **matrix, unsigned int m,
						unsigned int n);

/* parsing */
typedef struct s_map
{
	t_matrix		map;
	unsigned int	**color;
}					t_map;

t_map				parse_map(const char *filename);
t_matrix			map_to_vectors(t_map map);
t_matrix			get_isometric_projection(t_map map);
void				free_map(t_map map);

/* void wf_to_img(t_mlx_data mlx_data, t_img img, t_mat M, t_list *wf); */
void				wf_to_img(t_mlx_data mlx_data, t_img img, t_matrix M,
						t_map map);

typedef struct s_limits
{
	double			min_x;
	double			min_y;
	double			max_x;
	double			max_y;
}					t_limits;

t_limits			get_limits(t_matrix M);
unsigned int		get_scale(unsigned int size_x, unsigned int size_y,
						t_limits limits);

#endif // FDF_H
