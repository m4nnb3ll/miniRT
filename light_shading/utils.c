/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelayad <abelayad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 15:12:44 by abelayad          #+#    #+#             */
/*   Updated: 2023/10/29 20:14:43 by abelayad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
typedef struct s_material
{
	t_color	color;
	double	ambient;
	double	diffuse;
	double	specular;
	double	shininess;
	double	reflective; // [0.0-1.0]
	double	transparency;
	double	ri;// refractive index
}	t_material;
*/

t_material	ft_material(void)
{
	return ((t_material){g_white, .1, .7, .2, 200, 0, 0, GLASS});
}

t_tuple	ft_reflectv(t_tuple in, t_tuple n)
{
	return (ft_sub_tuples(in, ft_sclv(n, 2 * ft_dot(in, n))));
}

t_color	ft_checkers(t_obj *o, t_tuple pt)
{
	t_tuple	op;

	op = ft_transform_tuple(o->transform_inverse, pt);
	if ((int)(fabs(floor(op.x)) + fabs(floor(op.y))) % 2 == 0)
	{
		// printf("I return black from here 4\n");
		return (g_black);
	}
	return (o->material.color);
}

t_color	ft_tex_color_pl(t_comps *c)
{
	t_tuple	uv;
	t_color	color;

	uv = ft_planar_map(ft_transform_tuple(c->o->transform_inverse, c->pt));
	pthread_mutex_lock(&g_mtx);
	color = ft_uv_pattern_at(c->o->tex, uv.x, uv.y);
	pthread_mutex_unlock(&g_mtx);
	return (color);
	// 	t_tuple	uv;

	// uv = ft_planar_map(ft_transform_tuple(c->o->transform_inverse, c->pt));
	// t_color col = ft_uv_pattern_at(c->o->tex, uv.x, uv.y);
	// ft_print_color(col);
	// exit(42);
	// return (col);
}

t_tuple ft_spherical_map(t_tuple op)
{


  double theta = atan2(op.x, op.z);

  double phi = acos(op.y);

  double raw_u = theta / (2 * PI);

  double u = 1 - (raw_u + 0.5);

  double v = /* 1 -  */phi / PI; // it was "1 - phi / PI", but it reverses the texture upside down

  return ((t_tuple){u, v, 0, 1});
}

t_tuple ft_cylinderical_map(t_tuple op)
{
	double theta = atan2(op.x, op.z);
  	double raw_u = theta / (2 * PI);
  	double u = 1 - (raw_u + 0.5);
	double v = fabs(fmod(op.y, 1));

  return ((t_tuple){u, v, 0, 1});
}

t_color	ft_tex_color_sp(t_comps *c)
{
	t_tuple	uv;

	uv = ft_spherical_map(ft_transform_tuple(c->o->transform_inverse, c->pt));
	pthread_mutex_lock(&g_mtx);
	t_color col = ft_uv_pattern_at(c->o->tex, uv.x, uv.y);
	pthread_mutex_unlock(&g_mtx);
	// ft_print_color(col);
	// exit(42);
	return (col);
}

t_color	ft_tex_color_cy(t_comps *c)
{
	t_tuple	uv;
	t_color	color;

	uv = ft_cylinderical_map(ft_transform_tuple(c->o->transform_inverse, c->pt));
	pthread_mutex_lock(&g_mtx);
	color = ft_uv_pattern_at(c->o->tex, uv.x, uv.y);
	pthread_mutex_unlock(&g_mtx);
	return (color);
}


// ft_tex_color_at(hit -> o, comps.pt);
t_color	ft_tex_color_at(t_comps *comps)
{
	// t_tuple	uv;
	// t_tuple	op;
	// t_color	c;
	if (comps->o->type == OT_PLANE)
		return (ft_tex_color_pl(comps));
	if (comps->o->type == OT_SPHERE)
	{
		// exit(printf("I enter here in the sphere\n"));
		return (ft_tex_color_sp(comps));
	}
	if (comps->o->type == OT_CYLINDER || comps->o->type == OT_CONE)
		return (ft_tex_color_cy(comps));
	return (comps->o->material.color);
}

t_color	ft_get_obj_color(t_comps *comps)
{
	if (comps -> o -> checkered)
		return (ft_checkers(comps->o, comps->pt)); // i ll try later to pass comps only
	if (comps-> o -> tex.height)
	{
		// printf("%s>>>>>>>>>I enter the tex_color_at<<<<<<<<%s\n", GREEN, RESET_COLOR);
		return (ft_tex_color_at(comps));
	}
	// if (comps->o->type == OT_SPHERE)
	// 	(exit(printf("I didn't enter because comps-> o -> tex.height is: %d\n", comps-> o -> tex.height)));
	return (comps -> o -> material.color);
}
