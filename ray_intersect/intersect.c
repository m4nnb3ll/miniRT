/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelayad <abelayad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 16:08:09 by abelayad          #+#    #+#             */
/*   Updated: 2023/09/28 17:38:20 by abelayad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_xnode	*ft_intersect_sphere(t_objnode *o, t_ray r)
{
	t_quadratics	q;
	t_tuple			o_c;
	t_xnode			*xs;

	r = ft_transform_ray(o -> transform_inverse, r);
	o_c = ft_sub_tuples(r.origin, ft_point(0, 0, 0));
	q.a = ft_dot(r.direction, r.direction);
	q.b = 2 * ft_dot(o_c, r.direction);
	q.c = ft_dot(o_c, o_c) - 1;
	q.d = pow(q.b, 2) - 4 * q.a * q.c;
	xs = NULL;
	if (q.d >= 0)
	{
		xs = ft_xnew(o, (-q.b - sqrt(q.d)) / (2 * q.a));
		if (q.d > 0)
			ft_xadd_back(&xs, ft_xnew(o, (-q.b + sqrt(q.d)) / (2 * q.a)));
	}
	return (xs);
}

t_xnode	*ft_intersect_plane(t_objnode *o, t_ray r)
{
	double	t;

	// printf("I get inside intersect plane\n");
	r = ft_transform_ray(o -> transform_inverse, r);
	if (fabs(r.direction.z) < EPSILON)
		return (NULL);
	t = -r.origin.z / r.direction.z;
	if (t >= EPSILON)
		return (ft_xnew(o, t));
	return (NULL);
}

t_xnode	*ft_intersect_cylinder(t_objnode *o, t_ray r)
{
	t_quadratics	q;
	t_xnode			*xs;
	double			t;

	xs = NULL;
	r = ft_transform_ray(o -> transform_inverse, r);
	q.a = pow(r.direction.x, 2) + pow(r.direction.z, 2);
	if (q.a < EPSILON)
		return (ft_add_caps_cy(o, r, &xs));
	q.b = 2 * r.origin.x * r.direction.x + 2 * r.origin.z * r.direction.z;
	q.c = pow(r.origin.x, 2) + pow(r.origin.z, 2) - 1;
	q.d = pow(q.b, 2) - 4 * q.a * q.c;
	if (q.d >= 0)
	{
		t = (-q.b - sqrt(q.d)) / (2 * q.a);
		if (ft_pt_bound_cycone(o, r, t))
			xs = ft_xnew(o, t);
		if (q.d > 0)
		{
			t = (-q.b + sqrt(q.d)) / (2 * q.a);
			if (ft_pt_bound_cycone(o, r, t))
				ft_xadd_back(&xs, ft_xnew(o, t));
		}
	}
	return (ft_add_caps_cy(o, r, &xs));
}

t_xnode	*ft_intersect_cone(t_objnode *o, t_ray r)
{
	t_quadratics	q;
	t_xnode			*xs;

	xs = NULL;
	r = ft_transform_ray(o -> transform_inverse, r);
	q.a = pow(r.direction.x, 2) - pow(r.direction.y, 2) + pow(r.direction.z, 2);
	q.b = 2 * r.origin.x * r.direction.x
		- 2 * r.origin.y * r.direction.y + 2 * r.origin.z * r.direction.z;
	q.c = pow(r.origin.x, 2) - pow(r.origin.y, 2) + pow(r.origin.z, 2);
	if (!q.a && !q.b)
		return (ft_add_caps_cone(o, r, &xs));
	if (!q.a && q.b)
	{
		xs = ft_xnew(o, (-q.c) / (2 * q.b));
		return (ft_add_caps_cone(o, r, &xs));
	}
	q.d = pow(q.b, 2) - 4 * q.a * q.c;
	if (q.d >= 0)
		ft_intersect_cone_xs(&xs, q, o, r);
	return (ft_add_caps_cone(o, r, &xs));
}

t_xnode	*ft_intersect_world(t_world *w, t_ray r)
{
	int			i;
	t_xnode		*xs;

	char	*obj_types[] = {
		"OT_SPHERE",
		"OT_PLANE",
		"OT_CYLINDER",
		"OT_CONE"
	};
	(void)obj_types;


	xs = NULL;
	i = 0;
	while (i < w -> num_objs)
	{
		if (w->objs[i].type == OT_PLANE)
			ft_xadd_back(&xs, ft_intersect_plane(&w->objs[i++], r));
		else if (w->objs[i].type == OT_CYLINDER)
			ft_xadd_back(&xs, ft_intersect_cylinder(&w->objs[i++], r));
		else if (w->objs[i].type == OT_CONE)
			ft_xadd_back(&xs, ft_intersect_cone(&w->objs[i++], r));
		else
		{
			// printf("The transparency is: %f\n", w->objs[i].material.transparency);
			ft_xadd_back(&xs, ft_intersect_sphere(&w->objs[i++], r));
		}
	}
	return (ft_sort_xs(xs));
}
