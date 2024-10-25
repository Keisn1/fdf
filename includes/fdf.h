#ifndef FDF_H
#define FDF_H

/* gradient */
# ifdef __cplusplus

extern "C"
{
# endif

unsigned int *gradient(int width);



/* mlx */
typedef struct s_mlx_data {
	void *mlx_ptr;
	void *win_ptr;
} t_mlx_data;

typedef struct s_img{
	void *img; 				/* pointer to image in X-Server */
	char *img_pixels;		/* address of image data */
	int bpp;				/* bits per pixel */
	int size_line;
	int endian;
	int width;
	int height;
} t_img;

typedef struct s_pos{
	int x;
	int y;
} t_pos;

/* helpers */
int	create_rgb( int r, int g, int b);
void img_put_pixel(void *mlx_ptr, t_img *data, t_pos pos, unsigned int color);
void fill_img(void *mlx_ptr, t_img *img, unsigned int color);
t_img new_img(void *mlx_ptr, int width, int height);

/* line */
typedef struct s_line{
	double length;
	double phi;
	unsigned int color;
} t_line;

void draw_line_img(void *mlx_ptr, t_img *img, t_line line, t_pos pos);

/* rectangle */
typedef struct s_rectangle{
	int width;
	int height;
	unsigned int color;
} t_rectangle;

void draw_rect_win(t_mlx_data mlx_data, t_rectangle rect, t_pos pos);
void draw_rect_img(void *mlx_ptr, t_img *img, t_rectangle rect, t_pos pos);
t_rectangle new_rect(double width, double height, unsigned int color);

/* circle */
typedef struct s_circ {
	double r;
	unsigned int color;
} t_circ;

void draw_circ_win(t_mlx_data mlx_data, t_circ circ, t_pos pos);
void draw_circ_img(void *mlx_ptr, t_img *img, t_circ circ, t_pos pos);

/* triangle */
typedef struct s_triangle{
	double a;
	double b;
	double c;
	double alpha;
	double beta;
	double gamma;
} t_triangle;

t_triangle new_triangle(double a, double b, double c);
void draw_triangle_img(void *mlx_ptr, t_img *img, t_triangle t, t_pos pos);

#  ifdef __cplusplus

}
#  endif

#endif // FDF_H
