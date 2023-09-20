/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple_ops.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelayad <abelayad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 16:16:56 by abelayad          #+#    #+#             */
/*   Updated: 2023/09/20 16:18:34 by abelayad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_tuple	ft_add_tuples(t_tuple a, t_tuple b)
{
	return ((t_tuple){
		a.x + b.x,
		a.y + b.y,
		a.z + b.z,
		a.w + b.w
	});
}

t_tuple	ft_sub_tuples(t_tuple a, t_tuple b)
{
	return ((t_tuple){
		a.x - b.x,
		a.y - b.y,
		a.z - b.z,
		a.w - b.w
	});
}

double	ft_dot(t_tuple a, t_tuple b)
{
	return (
		a.x * b.x + a.y * b.y + a.z * b.z
	);
}

t_tuple	ft_cross(t_tuple a, t_tuple b)
{
	return (ft_vector(
			a.y * b.z - a.z * b.y,
			a.z * b.x - a.x * b.z,
			a.x * b.y - a.y * b.x
		));
}

t_tuple	ft_sclv(t_tuple a, double sclr)
{
	return ((t_tuple){
		a.x * sclr,
		a.y * sclr,
		a.z * sclr,
		0
	});
}
