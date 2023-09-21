/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuples.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelayad <abelayad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 16:18:14 by abelayad          #+#    #+#             */
/*   Updated: 2023/09/20 16:18:53 by abelayad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_tuple	ft_point(double x, double y, double z)
{
	return ((t_tuple){x, y, z, 1});
}

t_tuple	ft_vector(double x, double y, double z)
{
	return ((t_tuple){x, y, z, 0});
}

t_tuple	ft_negv(t_tuple a)
{
	return ((t_tuple){
		-a.x,
		-a.y,
		-a.z,
		0
	});
}

double	ft_mag(t_tuple v)
{
	return (sqrt(pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2)));
}

t_tuple	ft_normalize(t_tuple v)
{
	double	mag;

	mag = ft_mag(v);
	return (ft_vector(v.x / mag, v.y / mag, v.z / mag));
}
