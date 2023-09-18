#ifndef MINIRT_TYPES_H
# define MINIRT_TYPES_H

# define EPSILON		0.00001
# define SCREEN_WIDTH	1024
# define SCREEN_HEIGHT	1024
# define PPM_MAGIC_NUM	"P3"
# define PPM_MAX_COLOR	255
# define PI				3.14159265358979
# define RED			"\033[0;31m"
# define GREEN			"\033[0;32m"
# define YELLOW			"\033[0;33m"
# define RESET_COLOR	"\033[0m"
# define TRUE_S			GREEN"TRUE"RESET_COLOR
# define FALSE_S		RED"FALSE"RESET_COLOR
# define ENDIANESS		1

#include "MLX42.h"

// STOPPED HERE

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
	t_color	pixel_grid[SCREEN_WIDTH][SCREEN_HEIGHT];
}	t_canvas;

typedef struct s_matrix
{
	int			size;
	double	val[4][4];
}	t_matrix;

extern t_matrix	g_identity_matrix;

typedef struct s_ray
{
	t_tuple	origin;
	t_tuple	direction;
}	t_ray;

enum e_obj_type
{
	OT_SPHERE,
	OT_PLANE,
	OT_CYLINDER,
	OT_CONE
};

typedef struct s_material
{
	t_color	color;
	double	ambient;
	double	diffuse;
	double	specular;
	double	shininess;
}	t_material;

typedef struct s_plane {
	t_tuple	normal;
	t_tuple	pt;
}	t_plane;

typedef struct s_cone {
	double	height;
}	t_cone;

typedef struct s_obj
{
	enum e_obj_type		type;
	t_matrix			transform_inverse;
	t_material			material;
	void				*props;
	bool				checkered;
	struct s_obj		*next;
}	t_obj;

typedef struct s_xnode
{
	t_obj	*o;
	double		x;
	struct s_xnode	*next;
}	t_xnode;

// Structure to arrange quadratic solutions
typedef struct s_quadratics
{
	double	a;
	double	b;
	double	c;
	double	d;
}	t_quadratics;

typedef struct s_point_light
{
	t_tuple	position;
	t_color	color;
}	t_point_light;

typedef struct s_phong
{
	t_color	e_color;
	t_color	a_color;
	t_color	d_color;
	t_color	s_color;
	double	ldn; // light_dot_normal
	double	rde; // reflect_dot_eye
	double	spec_factor;
	t_tuple	lv;
	t_tuple	rv;
}	t_phong;

typedef struct s_comps
{
	t_obj	*o;
	double		x;
	t_tuple		pt;
	t_tuple		over_pt;
	t_tuple		ev;
	t_tuple		nv;
	bool		inside;
	bool		is_shadowed;
}	t_comps;

typedef struct s_camera
{
	t_tuple		pt;
	t_tuple		forward_v;// should be normalized
	double		fov;
	int			screen_w;
	int			screen_h;
	double		psize;
	double		half_c_w;
	double		half_c_h;
	t_matrix	view_transform_inverse;
}	t_camera;

/*---------DATACHECK-----------*/

typedef struct s_ambient
{
	double	ratio;
	t_color	color;// needs to be converted to range [0-1]
}	t_ambient;

typedef struct s_light
{
	t_tuple	position;
	float	brightness;
	t_color	color;
}	t_light;

typedef struct s_sphere
{
	t_tuple	pt;//position
	float	d;//diameter
}	t_sphere;

typedef struct s_cylinder
{
	t_tuple	center;
	t_tuple	axis;// should be normalized
	double	d; // diameter
	double	h; // height
}	t_cylinder;

typedef struct s_world
{
	t_ambient	ambient;
	t_camera	camera;
	t_light		lights[2];
	t_obj		*objs;
	int			num_objs; // number of objects
	int			num_lights;
}	t_world;

typedef struct s_find
{
	char **split;
}	t_find;

typedef struct s_count
{
	int	A;
	int C;
	int L;
	int l;
}	t_count;

typedef struct s_data
{
	t_find	*find;
	char	**map;
	int		mapsize;
}	t_data;

typedef struct s_window
{
	mlx_t		*mlx;
	mlx_image_t	*img;
}	t_window;

// TEST S
typedef struct s_texture
{
	int		width;
	int		height;
	t_color	**pixels;
}	t_texture;
// TEST E

#endif