#ifndef FDF_H
#define FDF_H


typedef struct s_pos{
	int x;
	int y;
} t_pos;

typedef struct s_img{
	void *img; 				/* pointer to image in X-Server */
	char *addr;				/* address of image data */
	int bpp;				/* bits per pixel */
	int size_line;
	int endian;
	int width;
	int height;
} t_img;


/* helpers */
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

void draw_rect_win(void* mlx_ptr, void *win_ptr, t_rectangle rect, t_pos pos);
void draw_rect_img(void *mlx_ptr, t_img *img, t_rectangle rect, t_pos pos);
t_rectangle new_rect(double width, double height, unsigned int color);

/* circle */
typedef struct s_circ {
	double r;
	unsigned int color;
} t_circ;

void draw_circ_win(void* mlx_ptr, void *win_ptr, t_circ circ, t_pos pos);
void draw_circ_img(void *mlx_ptr, t_img *img, t_circ circ, t_pos pos);

#endif // FDF_H
