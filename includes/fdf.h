#ifndef FDF_H
# define FDF_H

/* gradient */
# ifdef __cplusplus

extern "C"
{
# endif

# include "libft.h"
# include <stdbool.h>

	struct				s_bres
	{
		int				dx;
		int				sx;
		int				dy;
		int				sy;
		int				err;
		int				e2;
	};

	typedef struct s_point
	{
		unsigned int	i;
		unsigned int	j;
	} t_point;

	/* mlx */
	typedef struct s_mlx_data
	{
		void			*mlx_ptr;
		void			*win_ptr;
	} t_mlx_data;

	typedef int			(*PixelPutFunc)(void *, void *, int, int, int);
	int my_mlx_pixel_put(void *mlx_ptr, void *win_ptr, int x, int y, int color);
	void bres_plotline(t_mlx_data mlx_data, t_point p_0, t_point p_1,
		PixelPutFunc pixel_put);
	t_list *get_bres_line(t_point p_0, t_point p_1);

	typedef struct s_mat
	{
		double			**mat;
		int				m;
		int				n;
	} t_mat;

	void free_matrix(t_mat M);
	t_mat mat_mul(t_mat X, t_mat Y);
	t_mat get_rot_matrix();

	t_list *get_wireframe_indices(size_t wf_m, size_t wf_n);

	/* helpers */
	void add_back_point(t_list **l, t_point p);
	void print_matrix(double** matrix, unsigned int m, unsigned int n);

	/* parsing */
	typedef struct s_map
	{
		double			**map;
		unsigned int	**color;
		unsigned int	m;
		unsigned int	n;

	} t_map;

	t_map parse_map(const char *filename);
	t_mat extract_points(t_map map);

	/* void draw_rect_win(void* mlx_ptr, void* win_ptr, int p1, int p2,
		PixelPutFunc pixel_put); */
	/* /\* the real stuff *\/ */
	/* t_points new_circle(t_point mp, double r, size_t size); */

	typedef struct s_img
	{
		void *img;        /* pointer to image in X-Server */
		char *img_pixels; /* address of image data */
		int bpp;          /* bits per pixel */
		int				size_line;
		int				endian;
		int				width;
		int				height;
	} t_img;

	t_img new_img(void *mlx_ptr, int width, int height);
	void img_put_pixel(void *mlx_ptr, t_img *img, t_point pos,
		unsigned int color);
	void wf_to_img(t_mlx_data mlx_data, t_img img, t_mat M, t_list *wf);
	/* /\* helpers *\/ */
	/* int	create_rgb( int r, int g, int b); */
	/* void img_put_pixel(void *mlx_ptr, t_img *data, t_point pos,
		unsigned int color); */
	/* void fill_img(void *mlx_ptr, t_img *img, unsigned int color); */
	/* t_img new_img(void *mlx_ptr, int width, int height); */

	/* /\* line *\/ */
	/* typedef struct s_line{ */
	/* 	double length; */
	/* 	double phi; */
	/* 	unsigned int color; */
	/* } t_line; */

	/* void draw_line_img(void *mlx_ptr, t_img *img, t_line line,
		t_point pos); */

	/* /\* rectangle *\/ */
	/* typedef struct s_rectangle{ */
	/* 	int width; */
	/* 	int height; */
	/* 	unsigned int color; */
	/* } t_rectangle; */

	/* void draw_rect_win(t_mlx_data mlx_data, t_rectangle rect,
		t_point pos); */
	/* void draw_rect_img(void *mlx_ptr, t_img *img, t_rectangle rect,
		t_point pos); */
	/* t_rectangle new_rect(double width, double height, unsigned int color); */

	/* /\* circle *\/ */
	/* typedef struct s_circ { */
	/* 	double r; */
	/* 	unsigned int color; */
	/* } t_circ; */

	/* void draw_circ_win(t_mlx_data mlx_data, t_circ circ, t_point pos); */
	/* void draw_circ_img(void *mlx_ptr, t_img *img, t_circ circ,
		t_point pos); */

	/* /\* triangle *\/ */
	/* typedef struct s_triangle{ */
	/* 	double a; */
	/* 	double b; */
	/* 	double c; */
	/* 	double alpha; */
	/* 	double beta; */
	/* 	double gamma; */
	/* } t_triangle; */

	/* t_triangle new_triangle(double a, double b, double c); */
	/* void draw_triangle_img(void *mlx_ptr, t_img *img, t_triangle t,
		t_point pos); */

# ifdef __cplusplus
}
# endif

#endif // FDF_H
