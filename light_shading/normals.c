/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelayad <abelayad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 15:12:40 by abelayad          #+#    #+#             */
/*   Updated: 2023/12/03 21:56:03 by abelayad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_tuple	ft_obj_normal(t_obj *o, t_tuple wp)
{
	t_tuple	op;

	op = ft_transform_tuple(o -> transform_inverse, wp);
	if (o -> type == OT_PLANE)
		return (ft_get_pl_normal(o, op));
	else if (o -> type == OT_CYLINDER)
		return (ft_get_cy_normal(op));
	else if (o -> type == OT_CONE)
		return (ft_get_cn_normal(op));
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
