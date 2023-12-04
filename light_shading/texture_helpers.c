/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelayad <abelayad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 17:22:09 by abelayad          #+#    #+#             */
/*   Updated: 2023/12/02 17:34:21 by abelayad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color	ft_checkers(t_obj *o, t_tuple pt)
{
	t_tuple	op;

	op = ft_transform_tuple(o->transform_inverse, pt);
	if ((int)(fabs(floor(op.x)) + fabs(floor(op.y))) % 2 == 0)
		return (g_black);
	return (o->material.color);
}

t_color	ft_tex_color_pl(t_comps *c)
{
	t_tuple	uv;

	uv = ft_planar_map(ft_transform_tuple(c->o->transform_inverse, c->pt));
	return (ft_uv_pattern_at(c->o->tex, uv.x, uv.y));
}

t_color	ft_tex_color_sp(t_comps *c)
{
	t_tuple	uv;
	t_color	col;

	uv = ft_spherical_map(ft_transform_tuple(c->o->transform_inverse, c->pt));
	col = ft_uv_pattern_at(c->o->tex, uv.x, uv.y);
	return (col);
}

t_color	ft_tex_color_cy(t_comps *c)
{
	t_tuple	uv;

	uv = ft_cylinderical_map(
			ft_transform_tuple(c->o->transform_inverse, c->pt));
	return (ft_uv_pattern_at(c->o->tex, uv.x, uv.y));
}

t_color	ft_tex_color_at(t_comps *comps)
{
	if (comps->o->type == OT_PLANE)
		return (ft_tex_color_pl(comps));
	if (comps->o->type == OT_SPHERE)
		return (ft_tex_color_sp(comps));
	if (comps->o->type == OT_CYLINDER || comps->o->type == OT_CONE)
		return (ft_tex_color_cy(comps));
	return (comps->o->material.color);
}
