/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelayad <abelayad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 15:12:44 by abelayad          #+#    #+#             */
/*   Updated: 2023/09/26 22:31:43 by abelayad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_material	ft_material(void)
{
	return ((t_material){g_white, .1, .9, .9, 200});
}

t_tuple	ft_reflectv(t_tuple in, t_tuple n)
{
	return (ft_sub_tuples(in, ft_sclv(n, 2 * ft_dot(in, n))));
}

t_color	ft_checkers(t_obj *o, t_tuple pt)
{
	t_tuple	op;

	// if (!o -> checkered)
	// 	return (o->material.color);
	op = ft_transform_tuple(o->transform_inverse, pt);
	if ((int)(fabs(floor(op.x)) + fabs(floor(op.y))) % 2 == 0)
		return (g_black);
	return (g_white);
}

t_color	ft_get_obj_color(t_comps *comps)
{
	if (comps -> o -> type == OT_PLANE)
		return (ft_checkers(comps->o, comps->pt));
	return (comps -> o -> material.color);
}
