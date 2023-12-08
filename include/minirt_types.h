/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_types.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelayad <abelayad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 13:46:27 by abelayad          #+#    #+#             */
/*   Updated: 2023/12/08 10:20:22 by abelayad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_TYPES_H
# define MINIRT_TYPES_H

# define EPSILON		0.00001
# define SCREEN_WIDTH	1920
# define SCREEN_HEIGHT	1080
# define PI				3.14159265358979
# define RED			"\033[0;31m"
# define GREEN			"\033[0;32m"
# define YELLOW			"\033[0;33m"
# define WHITE			"\033[0;37m"
# define RESET_COLOR	"\033[0m"
# define REFLECT_DEPTH	5
// Material refract indices
# define VACUUM		1
# define AIR		1.00029
# define WATER		1.333
# define GLASS		1.52
# define DIAMOND	2.417

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

/*
	double	reflective; // [0.0-1.0]
	double	transparency; // [0.0-1.0]
	double	ri;// refractive index
*/
typedef struct s_material
{
	t_color	color;
	double	ambient;
	double	diffuse;
	double	specular;
	double	shininess;
	double	reflective;
	double	transparency;
	double	ri;
}	t_material;

typedef struct s_tex
{
	int		width;
	int		height;
	t_color	**pixels;
}	t_tex;

// btex: bump map texture
typedef struct s_plane {
	t_tuple	normal;
	t_tuple	pt;
	t_tex	*btex;
}	t_plane;

typedef struct s_obj
{
	enum e_obj_type	type;
	t_matrix		transform_inverse;
	t_material		material;
	bool			checkered;
	t_tex			tex;
	t_tex			btex;
	struct s_obj	*next;
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
	t_tuple		under_pt;
	t_tuple		ev;
	t_tuple		nv;
	t_tuple		rv;
	bool		inside;
	double		ns[2];
}	t_comps;

typedef struct s_camera
{
	t_tuple		from;
	t_tuple		to;
	double		fov;
	int			screen_w;
	int			screen_h;
	double		psize;
	double		half_c_w;
	double		half_c_h;
	t_matrix	view_transform_inverse;
	bool		set;
}	t_camera;

typedef struct s_light
{
	t_tuple			position;
	t_color			color;
	struct s_light	*next;
}	t_light;

typedef struct s_world
{
	t_camera		camera;
	t_light			*light_lst;
	t_obj			*obj_lst;
	int				cores_cnt;
	int				lines_progress;
	pthread_mutex_t	progress_mtx;
}	t_world;

typedef struct s_png_img
{
	int			width;
	int			height;
	png_bytep	*row_pointers;
}	t_png_img;

typedef struct s_contnode
{
	t_obj				*o;
	struct s_contnode	*next;
}	t_contnode;

enum	e_el_type
{
	EL_TYPE_C,
	EL_TYPE_L,
	EL_TYPE_SP,
	EL_TYPE_PL,
	EL_TYPE_CY,
	EL_TYPE_CN,
	EL_TYPE_ERR
};

typedef struct s_tbn
{
	t_tuple		normal;
	t_tuple		tang;
	t_tuple		binorm;
	t_matrix	matrix;
}	t_tbn;

#endif
