/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelayad <abelayad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 16:09:43 by abelayad          #+#    #+#             */
/*   Updated: 2023/10/26 23:42:38 by abelayad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	ft_print_tuple(t_tuple t)
{ printf(">>%f %f %f %f<<\n", t.x, t.y, t.z, t.w); }

void	ft_print_color(t_color c)
{ printf(">>%f %f %f<<\n", c.r, c.g, c.b); }

void	ft_print_camera(t_camera c)
{
	printf("%sThe camera >>>>>>>>>>>>>>>>>>>>>>>>>>\n%s", GREEN, RESET_COLOR);
	printf("from: ");
	ft_print_tuple(c.from);
	printf("to: ");
	ft_print_tuple(c.to);
	printf("fov: %f\n", c.fov);
	// printf("scree_w: %d\n", c.screen_w);
	// printf("scree_h: %d\n", c.screen_h);
	// printf("psize: %f\n", c.psize);
	// printf("half_c_w: %f\n", c.half_c_w);
	// printf("half_c_h: %f\n", c.half_c_h);
	// ft_print_matrix(c.view_transform_inverse);
	printf("set: %d\n", c.set);
	printf("%s<<<<<<<<<<<<<<<<<<<<<<<<<< The camera\n%s", RED, RESET_COLOR);
}

void	ft_print_light(t_light *light)
{
	printf("%sThe light >>>>>>>>>>>>>>>>>>>>>>>>>>\n%s", GREEN, RESET_COLOR);
	ft_print_tuple(light->position);
	ft_print_color(light->color);
	printf("%s<<<<<<<<<<<<<<<<<<<<<<<<<< The light\n%s", RED, RESET_COLOR);
}

void	ft_print_obj(t_obj *obj)
{
	char	*str_types[] = {
			"Sphere",
			"Plane",
			"Cylinder",
			"Cone",
		};


// 

	printf("%sThe object >>>>>>>>>>>>>>>>>>>>>>>>>>\n%s", GREEN, RESET_COLOR);
	printf("type: [[%s]]\n", str_types[obj->type]);
	printf("color: ");
	ft_print_color(obj->material.color);
	printf("checkered is: %d\n", obj->checkered);
	if (obj->tex.pixels)
		(printf("The tex is: "), ft_print_color(**obj->tex.pixels));
	if (obj->btex.pixels)
		(printf("The btex is: "), ft_print_color(**obj->btex.pixels));
	printf("%s<<<<<<<<<<<<<<<<<<<<<<<<<< The object\n%s", RED, RESET_COLOR);
}


void	ft_print_lights(t_light *light_lst)
{
	t_light	*tmp;

	tmp = light_lst;
	while (tmp)
	{
		ft_print_light(tmp);
		tmp = tmp -> next;
	}
}

void	ft_print_objs(t_obj *obj_lst)
{
	t_obj	*tmp;

	tmp = obj_lst;
	while (tmp)
	{
		ft_print_obj(tmp);
		tmp = tmp -> next;
	}
}

// u & v [0-1.0]
t_color	ft_uv_pattern_at(t_tex texture, double u, double v)
{
	int	x;
	int	y;

	if (!texture.pixels)
		return (g_black);
	// printf("I proceed!\n");
	x = (int)floor(u * (texture.width)) % texture.width;
	y = (int)floor(v * (texture.height)) % texture.height;
	// There is a problem here to check later
	if (x >= texture.width || x<0 || y<0 || y >= texture.height)
		exit(printf("out of bounds [%d][%d]\n", x, y));
	// printf("The color from texture here is:\n");
	// ft_print_color(texture.pixels[y][x]);
	return (texture.pixels[y][x]);
}

// take only the x and y
t_tuple	ft_planar_map(t_tuple op)
{
	return ((t_tuple){fabs(fmod(op.x, 1)), fabs(fmod(op.y, 1)), 0, 1});
}


/*
typedef struct s_ambient
{
	double	ratio;
	t_color	color;
}	t_ambient;

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
}	t_camera;

typedef struct s_light
{
	t_tuple	position;
	float	brightness;
	t_color	color;
	struct s_light	*next;
}	t_light;

typedef struct s_obj
{
	enum e_obj_type	type;
	t_matrix		transform_inverse;
	t_material		material;
	bool			checkered;
	t_tex			tex;
	t_tex			btex;
	void			*props;
	struct s_obj	*next;
}	t_obj;

typedef struct s_world
{
	t_ambient	ambient;
	t_camera	camera;
	t_light		lights[2];
	t_obj		*objs;
	int			num_objs;
	int			num_lights;
}	t_world;
*/

t_sphere	*ft_sphere(t_tuple pt, double d);


int	main(int argc, char **argv)
{
	t_world		w;
	t_png_img	img;

	(void)argc;
	(void)argv;
	if (argc != 2)
		return (printf("Please provide a scene file!\n"), -42);
	img = ft_allocate_png_img(SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!img.row_pointers)
		return (printf("Error allocating the image\n"), -42);
	// w.ambient = (t_ambient){.1, g_white};
	// w.camera.from = ft_point(0, 1, -5);
	// w.camera.to = ft_point(0, 0, 0);
	// w.camera.fov = PI/3;
	// w.camera = ft_camera(w.camera);
	// w.lights[0].position = ft_point(-10, 10, -10);
	// w.lights[0].brightness = 0.1;
	// w.lights[0].color = ft_color(1, 1, 1);
	// w.num_lights = 1;
	// w.num_objs = 1;
	// w.objs = ft_calloc(1, sizeof(t_obj));
	// ft_bzero(&w.objs[0], sizeof(t_obj));
	// w.objs[0].type = OT_SPHERE;
	// w.objs[0].transform_inverse = g_identity_matrix;
	// w.objs[0].material = ft_material();
	// w.objs[0].material.color = ft_color(1, 0, 0);
	// w.objs[0].props = ft_sphere(ft_point(0,0,0), 1);
	w = ft_parse_rt_file(argv[1]);
	// ft_print_camera(w.camera);
	// ft_print_lights(w.light_lst);
	// ft_print_objs(w.obj_lst);
	ft_render(img, &w, w.camera);
}



// ft_parse_rt_file(argv[1]);