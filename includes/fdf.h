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
# include "mlx_helper.h"
# include <X11/keysym.h>
# include <limits.h>
# include <stdbool.h>
# include <sys/wait.h>
# include <unistd.h>

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

typedef struct s_mat
{
	double			**mat;
	int				m;
	int				n;
}					t_matrix;

void				free_matrix(t_matrix M);
t_matrix			mat_mul(t_matrix X, t_matrix Y);
t_matrix			get_rot_matrix(void);

t_list				*get_wireframe_indices(size_t wf_m, size_t wf_n);

/* helpers */
void				add_back_point(t_list **l, t_point p);
void				print_matrix(double **matrix, unsigned int m,
						unsigned int n);

/* parsing */
typedef struct s_map
{
	double			**map;
	unsigned int	**color;
	unsigned int	m;
	unsigned int	n;

}					t_map;

t_map				parse_map(const char *filename);
t_matrix			extract_points(t_map map);
void				free_map(t_map map);

typedef struct s_img
{
	void *img;        /* pointer to image in X-Server */
	char *img_pixels; /* address of image data */
	int bpp;          /* bits per pixel */
	int				size_line;
	int				endian;
	int				width;
	int				height;
}					t_img;

t_img				new_img(void *mlx_ptr, int width, int height);
void				img_put_pixel(void *mlx_ptr, t_img *img, t_point pos,
						unsigned int color);

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
