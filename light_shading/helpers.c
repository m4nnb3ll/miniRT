/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelayad <abelayad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 15:12:44 by abelayad          #+#    #+#             */
/*   Updated: 2023/12/04 19:10:02 by abelayad         ###   ########.fr       */
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

t_color	ft_get_obj_color(t_comps *comps)
{
	// test
	// printf("The tex and btex are: %d %d\n", comps->o->tex.height, comps->o->btex.height);
	// exit(11);
	// test
	if (comps-> o -> tex.height)
		return (ft_tex_color_at(comps));
	if (comps -> o -> checkered)
		return (ft_checkers(comps->o, comps->pt));
	return (comps -> o -> material.color);
}

// it was "v = 1 - phi / PI", but it reverses the texture upside down
t_tuple	ft_spherical_map(t_tuple op)
{
	double	theta;
	double	phi;
	double	raw_u;
	double	u;
	double	v;

	theta = atan2(op.x, op.z);
	phi = acos(op.y);
	raw_u = theta / (2 * PI);
	u = 1 - (raw_u + 0.5);
	v = phi / PI;
	return ((t_tuple){u, v, 0, 1});
}

t_tuple	ft_cylinderical_map(t_tuple op)
{
	double	theta;
	double	raw_u;
	double	u;
	double	v;

	theta = atan2(op.x, op.z);
	raw_u = theta / (2 * PI);
	u = 1 - (raw_u + 0.5);
	v = fabs(fmod(op.y, 1));
	return ((t_tuple){u, v, 0, 1});
}
