
#include "include/minirt.h"
// for position, call ft_point(x, y, z);
/*
	for vector, call ft_vector(x, y, z);
	If a vector should be normalized, and it's not normalized throw error.
	To know if a vector is normalized, its magnitude should be equal to 1.
	There is the function `ft_mag()` that calculates the magnitude.
*/
// for color, check ft_color(r, g, b);

typedef struct s_ambient
{
	float	ratio;
	t_color	color;// needs to be converted to range [0-1]
}	t_ambient;

typedef struct s_camera
{
	t_tuple		position;
	t_tuple		forward_v;// should be normalized
	double		fov;// convert from degrees to radians
}	t_camera;

typedef struct s_light
{
	t_tuple	position;
	float	brightness;
	t_color	color;
}	t_light;

typedef struct s_world
{
	t_ambient	ambient;
	t_camera	camera;
	t_light		light;
	t_obj		*objects;
}	t_world;

// Objects

// Each object has a type:
enum e_obj_type
{
	OT_SPHERE,
	OT_PLANE,
	OT_CYLINDER,
	OT_CONE
};

typedef struct s_obj
{
	enum e_obj_type		type;
	t_material			material;
	void				*props;
}	t_obj;

// For color, put it in `material.color` in the struct above

// The props can be typecasted in one of the following types

typedef struct s_sphere
{
	t_tuple	position;
	float	diameter;
}	t_sphere;

typedef struct s_plane {
	t_tuple	position;
	t_tuple	normal;
}	t_plane;

typedef struct s_cylinder {
	t_tuple	center;
	t_tuple	axis;// should be normalized
	float	diameter;
	float	height;
}	t_cylinder;