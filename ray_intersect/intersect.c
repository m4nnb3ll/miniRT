/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelayad <abelayad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 16:08:09 by abelayad          #+#    #+#             */
/*   Updated: 2023/10/25 22:39:22 by abelayad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// original goes below
t_xnode	*ft_intersect_sphere(t_obj *o, t_ray r)
{
	t_quadratics	q;
	t_tuple			o_c;
	t_xnode			*xs;

	r = ft_transform_ray(o -> transform_inverse, r);
	o_c = ft_sub_tuples(r.origin, ft_point(0, 0, 0));
	q.a = ft_dot(r.direction, r.direction);
	q.b = 2 * ft_dot(o_c, r.direction);
	q.c = ft_dot(o_c, o_c) - 1;// sphere with radius of one simplifies calculation
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

t_xnode	*ft_intersect_plane(t_obj *o, t_ray r)
{
	double	t;

	r = ft_transform_ray(o -> transform_inverse, r);
	if (fabs(r.direction.z) < EPSILON)
		return (NULL);
	t = -r.origin.z / r.direction.z;
	if (t >= EPSILON)
		return (ft_xnew(o, t));
	return (NULL);
}

t_xnode	*ft_intersect_cylinder(t_obj *o, t_ray r)
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
	q.c = pow(r.origin.x, 2) + pow(r.origin.z, 2) - .25;
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

t_xnode	*ft_intersect_cone(t_obj *o, t_ray r)
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

void	ft_print_matrix(t_matrix m)
{
	int	i, j;

	i = 0;
	while (i < m.size)
	{
		j = 0;
		while (j < m.size)
		{
			printf("%f ", m.val[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
	printf("The print of matrix is done\n");
}

void	ft_print_material(t_material m)
{
	printf("The color is: ");
	ft_print_color(m.color);
	printf("The ambient is: %f\n", m.ambient);
	printf("The diffuse is: %f\n", m.diffuse);
	printf("The specular is: %f\n", m.specular);
	printf("The shininess is: %f\n", m.shininess);
	
}

t_xnode	*ft_intersect_world(t_world *w, t_ray r)
{
	t_obj		*tmp_o;
	t_xnode		*xs;

	xs = NULL;
	tmp_o = w->obj_lst;
	while (tmp_o)
	{
		if (tmp_o->type == OT_PLANE)
			ft_xadd_back(&xs, ft_intersect_plane(tmp_o, r));
		else if (tmp_o->type == OT_CYLINDER)
			ft_xadd_back(&xs, ft_intersect_cylinder(tmp_o, r));
		else if (tmp_o->type == OT_CONE)
			ft_xadd_back(&xs, ft_intersect_cone(tmp_o, r));
		else
		{
			ft_xadd_back(&xs, ft_intersect_sphere(tmp_o, r));
			// printf("The obj goes below\n");
			// ft_print_obj(tmp_o);
			// printf("The matric goes below\n");
			// ft_print_matrix(tmp_o->transform_inverse);
			// printf("The object's material is:\n");
			// ft_print_material(tmp_o->material);
			// exit(42);
		}
		tmp_o = tmp_o -> next;
	}
	return (xs);
}
