#include "minirt.h"

t_xnode	*ft_intersect_sphere(t_obj *o, t_ray r)
{
	t_quadratics	q;
	t_tuple				o_c;
	t_xnode				*xs;

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

// STOPPED INVESTIGATING THE ACNE

t_xnode	*ft_intersect_plane(t_obj *o, t_ray r)
{
	// printf("The ray");
	r = ft_transform_ray(o -> transform_inverse, r);
	if (fabs(r.direction.y) < EPSILON)
	{
		// printf("I enter the NULL\n");
		return (NULL);
	}
	// printf("r.direction.y is: %f\n", r.direction.y);
	return (ft_xnew(o, - r.origin.y / r.direction.y));
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

t_xnode	*ft_intersect_obj(t_obj *o, t_ray r)
{
	if (o -> type == OT_PLANE)
		return (ft_intersect_plane(o, r));
	return (ft_intersect_sphere(o, r));
}

t_xnode	*ft_intersect_world(t_world w, t_ray r)
{
	t_obj	*tmp_obj;
	t_xnode		*xs;

	tmp_obj = w.objlst;
	xs = NULL;
	while (tmp_obj)
	{
		ft_xadd_back(&xs, ft_intersect_obj(tmp_obj, r));
		tmp_obj = tmp_obj -> next;
	}
	return (xs);
}
