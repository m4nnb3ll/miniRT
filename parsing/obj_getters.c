/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_getters.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelayad <abelayad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 17:12:11 by abelayad          #+#    #+#             */
/*   Updated: 2023/12/04 19:12:18 by abelayad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// below doing 'd / 2' because the default sphere is of radius 1.
bool	ft_get_sp(char *s, t_world *w)
{
	t_obj		*o;
	t_tuple		pt;
	double		d;

	ft_skip_token(&s);
	o = ft_objnew(OT_SPHERE);
	if (!ft_get_tuple(&s, &pt, true)
		|| !ft_get_double(&s, &d)
		|| !ft_get_color(&s, &o->material.color)
		|| !ft_get_double(&s, &o->material.reflective)
		|| !ft_get_double(&s, &o->material.transparency)
		|| !ft_get_double(&s, &o->material.ri)
		|| !ft_get_optional_obj_params(&s, o))
		return (false);
	o -> transform_inverse = ft_inverse(
			ft_multi_matrices(
				ft_translate(pt.x, pt.y, pt.z),
				ft_scale(d / 2, d / 2, d / 2)
				)
			);
	if (!o->material.ri)
		o->material.ri = GLASS;
	ft_objadd_back(&w->obj_lst, o);
	return (true);
}

bool	ft_get_pl(char *s, t_world *w)
{
	t_obj		*o;
	t_tuple		pt;
	t_tuple		normal;

	ft_skip_token(&s);
	o = ft_objnew(OT_PLANE);
	if (!ft_get_tuple(&s, &pt, true)
		|| !ft_get_tuple(&s, &normal, false)
		|| !ft_get_color(&s, &o->material.color)
		|| !ft_get_double(&s, &o->material.reflective)
		|| !ft_get_double(&s, &o->material.transparency)
		|| !ft_get_double(&s, &o->material.ri)
		|| !ft_get_optional_obj_params(&s, o))
		return (false);
	if (!(o->material.color.r + o->material.color.g + o->material.color.b))
		o->material.specular = 0;
	o -> transform_inverse = ft_inverse(
			ft_multi_matrices(
				ft_translate(pt.x, pt.y, pt.z),
				ft_get_rotation_matrix(ft_vector(0, 0, 1), normal)
				)
			);
	if (!o->material.ri)
		o->material.ri = GLASS;
	ft_objadd_back(&w->obj_lst, o);
	return (true);
}

bool	ft_get_cycone(char *s, t_world *w, enum e_obj_type type)
{
	t_obj	*o;
	t_tuple	pt;
	t_tuple	dir_v;
	double	d;
	double	h;

	ft_skip_token(&s);
	o = ft_objnew(type);
	if (!ft_get_tuple(&s, &pt, true) || !ft_get_tuple(&s, &dir_v, false)
		|| !ft_get_double(&s, &d) || !ft_get_double(&s, &h)
		|| !ft_get_color(&s, &o->material.color)
		|| !ft_get_double(&s, &o->material.reflective)
		|| !ft_get_double(&s, &o->material.transparency)
		|| !ft_get_double(&s, &o->material.ri)
		|| !ft_get_optional_obj_params(&s, o))
		return (false);
	o -> transform_inverse = ft_inverse(
			ft_multi_matrices(ft_translate(pt.x, pt.y, pt.z), ft_multi_matrices(
					ft_get_rotation_matrix(ft_vector(0, 1, 0), dir_v),
					ft_scale(d, h, d))));
	if (!o->material.ri)
		o->material.ri = GLASS;
	ft_objadd_back(&w->obj_lst, o);
	return (true);
}
