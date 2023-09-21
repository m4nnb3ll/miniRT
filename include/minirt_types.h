/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_types.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelayad <abelayad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 13:46:27 by abelayad          #+#    #+#             */
/*   Updated: 2023/09/20 17:26:58 by abelayad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
# define ENDIANESS		1

// # include "MLX42.h" TESTING LEAKS

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

extern const t_color	g_black;
extern const t_color	g_white;
extern const t_color	g_red;
extern const t_color	g_green;
extern const t_color	g_blue;

typedef struct s_canvas {
	t_color	pixel_grid[SCREEN_WIDTH][SCREEN_HEIGHT];
}	t_canvas;

typedef struct s_matrix
{
	int			size;
	double		val[4][4];
}	t_matrix;

extern const t_matrix	g_identity_matrix;

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

typedef struct s_btex
{
	t_color	**pixels;
	char	**read;
	char	**leaks;
	int		width;
	int		height;
}	t_btex;

// btex: bump map texture
typedef struct s_plane {
	t_tuple	normal;
	t_tuple	pt;
	t_btex	*btex;
}	t_plane;

// typedef struct s_cone {
// 	double	height;
// }	t_cone;

typedef struct s_obj
{
	enum e_obj_type		type;
	t_matrix			transform_inverse;
	t_material			material;
	void				*props;
	bool				checkered;
	t_btex				*btex;
	struct s_obj		*next;
}	t_obj;

typedef struct s_xnode
{
	t_obj			*o;
	double			x;
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

// ldn: light_dot_normal
// rde: reflect_dot_eye

typedef struct s_phong
{
	t_color	e_color;
	t_color	a_color;
	t_color	d_color;
	t_color	s_color;
	double	ldn;
	double	rde;
	double	spec_factor;
	t_tuple	lv;
	t_tuple	rv;
}	t_phong;

typedef struct s_comps
{
	t_obj		*o;
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
	t_tuple		forward_v;
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
	t_color	color;
}	t_ambient;

typedef struct s_light
{
	t_tuple	position;
	float	brightness;
	t_color	color;
}	t_light;

/*
	pt: position
	d: diameter
*/
typedef struct s_sphere
{
	t_tuple	pt;
	float	d;
}	t_sphere;

/*
	d: diameter
	h: height
*/
typedef struct s_cylinder
{
	t_tuple	center;
	t_tuple	axis;
	double	d;
	double	h;
}	t_cylinder;

typedef struct s_cone
{
	t_tuple	center;
	t_tuple	axis;// should be normalized
	double	d; // diameter
	double	h; // height
}	t_cone;

typedef struct s_find
{
	char	**split;
}	t_find;

// ls: small l
typedef struct s_count
{
	int	a;
	int	c;
	int	l;
	int	ls;
}	t_count;

typedef struct s_data
{
	t_find	*find;
	char	**map;
	int		mapsize;
}	t_data;

// TESTING LEAKS
// typedef struct s_window
// {
// 	mlx_t		*mlx;
// 	mlx_image_t	*img;
// }	t_window;

typedef struct s_window
{
	void		*mlx;
	void		*img;
}	t_window;


typedef struct s_world
{
	t_ambient	ambient;
	t_camera	camera;
	t_light		lights[2];
	t_obj		*objs;
	int			num_objs;
	int			num_lights;
}	t_world;

#endif
