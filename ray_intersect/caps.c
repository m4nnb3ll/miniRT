/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   caps.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelayad <abelayad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 16:07:55 by abelayad          #+#    #+#             */
/*   Updated: 2023/12/05 15:37:29 by abelayad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	ft_check_cap_cy(t_ray r, double t)
{
	double	x;
	double	z;

	x = r.origin.x + t * r.direction.x;
	z = r.origin.z + t * r.direction.z;
	return (pow(x, 2) + pow(z, 2) <= 1);
}

bool	ft_check_cap_cone(t_ray r, double t)
{
	double	x;
	double	y;
	double	z;

	x = r.origin.x + t * r.direction.x;
	y = r.origin.y + t * r.direction.y;
	z = r.origin.z + t * r.direction.z;
	return (pow(x, 2) + pow(z, 2) <= pow(y, 2));
}

t_xnode	*ft_add_caps_cy(t_obj *cy, t_ray r, t_xnode **xs)
{
	double	t;
	double	half_height;

	if (fabs(r.direction.y) < EPSILON)
		return (*xs);
	half_height = .5;
	t = (-half_height - r.origin.y) / r.direction.y;
	if (ft_check_cap_cy(r, t))
		ft_xadd_back(xs, ft_xnew(cy, t));
	t = (half_height - r.origin.y) / r.direction.y;
	if (ft_check_cap_cy(r, t))
		ft_xadd_back(xs, ft_xnew(cy, t));
	return (*xs);
}

t_xnode	*ft_add_caps_cone(t_obj *cy, t_ray r, t_xnode **xs)
{
	double	t;
	double	half_height;

	if (fabs(r.direction.y) < EPSILON)
		return (*xs);
	half_height = .5;
	t = (-half_height - r.origin.y) / r.direction.y;
	if (ft_check_cap_cone(r, t))
		ft_xadd_back(xs, ft_xnew(cy, t));
	t = (half_height - r.origin.y) / r.direction.y;
	if (ft_check_cap_cone(r, t))
		ft_xadd_back(xs, ft_xnew(cy, t));
	return (*xs);
}
