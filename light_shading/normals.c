/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelayad <abelayad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 15:12:40 by abelayad          #+#    #+#             */
/*   Updated: 2023/10/29 20:10:57 by abelayad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"


t_tuple	ft_get_sp_normal(t_obj *sp, t_tuple op)
{
	t_tuple	uv;
	t_color	c;
	t_tuple		normal, tang, binorm;
	t_matrix	tbn;

	normal = ft_sub_tuples(op, ft_point(0, 0, 0));
	if (!sp -> btex.pixels) return (normal);
	// Calculate tangent and binormal vectors
	uv = ft_spherical_map(op);
	double theta = uv.x * (2 * PI);
	tang = ft_normalize(ft_vector(-sin(theta), 0, cos(theta)));
	binorm = ft_normalize(ft_cross(normal, tang));

	// Construct TBN matrix
	tbn =	((t_matrix){4, {
			{ tang.x, binorm.x, normal.x, 0 },
			{ tang.y, binorm.y, normal.y, 0 },
			{ tang.z, binorm.z, normal.z, 0 },
			{0, 0, 0, 1}
		}});

	// Transform texture coordinates into tangent space
	pthread_mutex_lock(&g_mtx);
	c = ft_uv_pattern_at(sp->btex, uv.x, uv.y);
	pthread_mutex_unlock(&g_mtx);
	uv = ft_normalize(ft_vector(2 * c.r - 1, 2 * c.g - 1, 2 * c.b - 1));
	uv = ft_transform_tuple(tbn, uv);

	return (ft_normalize(uv));
}


t_tuple	ft_get_pl_normal(t_obj *pl, t_tuple op)
{
	t_tuple	uv;
	t_color	c;

	if (!pl -> btex.pixels)
		return (ft_vector(0, 0, 1));
	uv = ft_planar_map(op);
	// printf("the op from the btex is:\n");
	// ft_print_tuple(op);
	// exit(42);
	pthread_mutex_lock(&g_mtx);
	c = ft_uv_pattern_at(pl->btex, uv.x, uv.y);
	pthread_mutex_unlock(&g_mtx);
	return (ft_normalize(ft_vector(2 * c.r - 1, 2 * c.g - 1, 2 * c.b - 1)));
}

t_tuple	ft_get_cy_normal(t_obj *cy, t_tuple op)
{
	double	half_height;
	double	d;

	(void)cy;
	half_height = .5;
	d = pow(op.x, 2) + pow(op.z, 2);
	if (d < 1 && op.y >= half_height - EPSILON)
		return (ft_vector(0, 1, 0));
	if (d < 1 && op.y <= -half_height + EPSILON)
		return (ft_vector(0, -1, 0));
	return (ft_vector(op.x, 0, op.z));
}

t_tuple	ft_get_cn_normal(t_obj *cone, t_tuple op)
{
	double	half_height;
	double	d;
	double	y;

	(void)cone;
	y = sqrt(pow(op.x, 2) + pow(op.z, 2)) * (-2 * (op.y > 0) + 1);
	half_height = .5;
	d = pow(op.x, 2) + pow(op.z, 2);
	if (d < 1 && op.y >= half_height - EPSILON)
		return (ft_vector(0, 1, 0));
	if (d < 1 && op.y <= -half_height + EPSILON)
		return (ft_vector(0, -1, 0));
	return (ft_vector(op.x, y, op.z));
}


t_tuple	ft_obj_normal(t_obj *o, t_tuple wp)
{
	t_tuple	op;

	op = ft_transform_tuple(o -> transform_inverse, wp);
	if (o -> type == OT_PLANE)
		return (ft_get_pl_normal(o, op));
	else if (o -> type == OT_CYLINDER)
		return (ft_get_cy_normal(o, op));
	else if (o -> type == OT_CONE)
		return (ft_get_cn_normal(o, op));
	else
		return (ft_get_sp_normal(o, op));
}

t_tuple	ft_normal_at(t_obj *o, t_tuple wp)
{
	t_tuple	on;
	t_tuple	wn;

	on = ft_normalize(ft_obj_normal(o, wp));
	wn = ft_transform_tuple(ft_transpose(o -> transform_inverse), on);
	wn.w = 0;
	return (ft_normalize(wn));
}
