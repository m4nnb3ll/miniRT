/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelayad <abelayad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 16:10:41 by abelayad          #+#    #+#             */
/*   Updated: 2023/09/20 16:10:44 by abelayad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// .5 is the height/2
bool	ft_pt_bound_cy(t_obj *o, t_ray r, double t)
{
	(void)o;
	if (fabs(r.origin.y + t * r.direction.y) < .5)
		return (true);
	return (false);
}

bool	ft_pt_bound_cone(t_obj *o, t_ray r, double t)
{
	(void)o;
	if (fabs(r.origin.y + t * r.direction.y) < .5)
		return (true);
	return (false);
}

t_xnode	*ft_hit(t_xnode *xlst)
{
	t_xnode	*hit;

	if (!xlst)
		return (NULL);
	hit = NULL;
	while (xlst)
	{
		if (xlst -> x >= 0 && (!hit || xlst -> x < hit -> x))
			hit = xlst;
		xlst = xlst -> next;
	}
	return (hit);
}

void	ft_intersect_cone_xs(t_xnode **xs, t_quadratics q, t_obj *o, t_ray r)
{
	double	t;

	t = (-q.b - sqrt(q.d)) / (2 * q.a);
	if (ft_pt_bound_cy(o, r, t))
		*xs = ft_xnew(o, t);
	if (q.d > 0)
	{
		t = (-q.b + sqrt(q.d)) / (2 * q.a);
		if (ft_pt_bound_cy(o, r, t))
			ft_xadd_back(xs, ft_xnew(o, t));
	}
}
