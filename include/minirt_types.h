#ifndef MINIRT_TYPES_H
# define MINIRT_TYPES_H

# define EPSILON				0.00001
# define CANVAS_WIDTH		10
# define CANVAS_HEIGHT	10
# define PPM_MAGIC_NUM	"P3"
# define PPM_MAX_COLOR	255
# define PI							3.14159265358979

typedef struct s_tuple
{
	double	x;
	double	y;
	double	z;
	double	w;
}	t_tuple;

// [0.0, 1.0]
typedef struct s_color
{
	double	r;
	double	g;
	double	b;
}	t_color;

extern t_color	g_black;
extern t_color	g_white;
extern t_color	g_red;
extern t_color	g_green;
extern t_color	g_blue;

typedef struct s_canvas {
	t_color	pixel_grid[CANVAS_WIDTH][CANVAS_HEIGHT];
}	t_canvas;

typedef struct s_matrix
{
	int			size;
	double	val[4][4];
}	t_matrix;

extern t_matrix	g_identity_matrix;

#endif