/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normals_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelayad <abelayad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 17:08:02 by abelayad          #+#    #+#             */
/*   Updated: 2023/12/03 21:56:13 by abelayad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// u & v [0-1.0]
t_color	ft_uv_pattern_at(t_tex texture, double u, double v)
{
	int	x;
	int	y;

	if (!texture.pixels)
	{
		// printf("I return black from here 1\n");
		return (g_black);
	}
	x = (int)floor(u * (texture.width)) % texture.width;
	y = (int)floor(v * (texture.height)) % texture.height;
	return (texture.pixels[y][x]);
}

/*
	// Calculating tangent and binormal vectors
		uv = ft_spherical_map(op);
		double theta = uv.x * (2 * PI);
		tang = ft_normalize(ft_vector(-sin(theta), 0, cos(theta)));
		binorm = ft_normalize(ft_cross(normal, tang));

	// Transform texture coordinates into tangent space
		c = ft_uv_pattern_at(sp->btex, uv.x, uv.y);
		uv = ft_normalize(ft_vector(2 * c.r - 1, 2 * c.g - 1, 2 * c.b - 1));
		uv = ft_transform_tuple(tbn, uv);
*/
t_tuple	ft_get_sp_normal(t_obj *sp, t_tuple op)
{
	t_tuple		uv;
	t_color		c;
	t_tbn		tbn;
	double		theta;

	tbn.normal = ft_sub_tuples(op, ft_point(0, 0, 0));
	if (!sp -> btex.pixels)
		return (tbn.normal);
	uv = ft_spherical_map(op);
	theta = uv.x * (2 * PI);
	tbn.tang = ft_normalize(ft_vector(-sin(theta), 0, cos(theta)));
	tbn.binorm = ft_normalize(ft_cross(tbn.normal, tbn.tang));
	tbn.matrix = ((t_matrix){4,
		{
		{tbn.tang.x, tbn.binorm.x, tbn.normal.x, 0},
		{tbn.tang.y, tbn.binorm.y, tbn.normal.y, 0},
		{tbn.tang.z, tbn.binorm.z, tbn.normal.z, 0},
		{0, 0, 0, 1}
		}});
	c = ft_uv_pattern_at(sp->btex, uv.x, uv.y);
	uv = ft_normalize(ft_vector(2 * c.r - 1, 2 * c.g - 1, 2 * c.b - 1));
	uv = ft_transform_tuple(tbn.matrix, uv);
	return (ft_normalize(uv));
}

// take only the x and y
t_tuple	ft_planar_map(t_tuple op)
{
	return ((t_tuple){fabs(fmod(op.x, 1)), fabs(fmod(op.y, 1)), 0, 0});
}

t_tuple	ft_get_pl_normal(t_obj *pl, t_tuple op)
{
	t_tuple	uv;
	t_color	c;

	if (!pl -> btex.pixels)
		return (ft_vector(0, 0, 1));
	uv = ft_planar_map(op);
	c = ft_uv_pattern_at(pl->btex, uv.x, uv.y);
	return (ft_normalize(ft_vector(2 * c.r - 1, 2 * c.g - 1, 2 * c.b - 1)));
}

t_tuple	ft_get_cy_normal(t_tuple op)
{
	double	half_height;
	double	d;

	half_height = .5;
	d = pow(op.x, 2) + pow(op.z, 2);
	if (d < 1 && op.y >= half_height - EPSILON)
		return (ft_vector(0, 1, 0));
	if (d < 1 && op.y <= -half_height + EPSILON)
		return (ft_vector(0, -1, 0));
	return (ft_vector(op.x, 0, op.z));
}

t_tuple	ft_get_cn_normal(t_tuple op)
{
	double	half_height;
	double	d;
	double	y;

	y = sqrt(pow(op.x, 2) + pow(op.z, 2)) * (-2 * (op.y > 0) + 1);
	half_height = .5;
	d = pow(op.x, 2) + pow(op.z, 2);
	if (d < 1 && op.y >= half_height - EPSILON)
		return (ft_vector(0, 1, 0));
	if (d < 1 && op.y <= -half_height + EPSILON)
		return (ft_vector(0, -1, 0));
	return (ft_vector(op.x, y, op.z));
}
