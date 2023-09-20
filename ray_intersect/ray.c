/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelayad <abelayad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 16:10:32 by abelayad          #+#    #+#             */
/*   Updated: 2023/09/20 16:10:33 by abelayad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_ray	ft_ray(t_tuple origin, t_tuple direction)
{
	return ((t_ray){origin, direction});
}

t_tuple	ft_pos_on_ray(t_ray r, double x)
{
	return (ft_add_tuples(r.origin, ft_sclv(r.direction, x)));
}

t_ray	ft_transform_ray(t_matrix m, t_ray r)
{
	r.origin = ft_transform_tuple(m, r.origin);
	r.direction = ft_transform_tuple(m, r.direction);
	return (r);
}
