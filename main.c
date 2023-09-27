/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelayad <abelayad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 16:09:43 by abelayad          #+#    #+#             */
/*   Updated: 2023/09/27 10:35:24 by abelayad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// u & v [0-1.0]
t_color	ft_uv_pattern_at(t_tex texture, double u, double v)
{
	int	x;
	int	y;

	if (!texture.pixels)
		return (g_black);
	x = (int)floor(u * (texture.width)) % texture.width;
	y = (int)floor(v * (texture.height)) % texture.height;
	return (texture.pixels[y][x]);
}

// take only the x and y
t_tuple	ft_planar_map(t_tuple op)
{
	return ((t_tuple){fabs(fmod(op.x, 1)), fabs(fmod(op.y, 1)), 0, 0});
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
	w.ambient = (t_ambient){.1, g_white};
	w.camera.from = ft_point(0, 1, -5);
	w.camera.to = ft_point(0, 0, 0);
	w.camera.fov = PI/3;
	w.camera = ft_camera(w.camera);
	w.lights[0].position = ft_point(-10, 10, -10);
	w.lights[0].brightness = 0.1;
	w.lights[0].color = ft_color(.5, .5, .5);
	w.num_lights = 1;
	w.num_objs = 1;
	w.objs = ft_calloc(1, sizeof(t_obj));
	ft_bzero(&w.objs[0], sizeof(t_obj));
	w.objs[0].type = OT_SPHERE;
	w.objs[0].transform_inverse = g_identity_matrix;
	w.objs[0].material = ft_material();
	w.objs[0].material.color = ft_color(255, 0, 0);
	w.objs[0].props = ft_sphere(ft_point(0,0,0), 1);
	ft_render(img, &w, w.camera);
}



// ft_parse_rt_file(argv[1]);
