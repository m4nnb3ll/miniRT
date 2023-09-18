#include "minirt.h"

t_xnode	*ft_intersect_sphere(t_obj *o, t_ray r)
{
	t_quadratics	q;
	t_tuple				o_c;
	t_xnode				*xs;

	// // TEST
	// o -> transform_inverse = ft_multi_matrices();
	// // TEST
	// o -> transform_inverse = g_identity_matrix;
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
	y = r.origin.y + t * r.direction.y; // On test
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

t_xnode	*ft_intersect_cylinder(t_obj *o, t_ray r)
{
	t_quadratics	q;
	t_xnode			*xs;
	double			t;

	xs = NULL;
	r = ft_transform_ray(o -> transform_inverse, r);
	// o_c = ft_sub_tuples(r.origin, ft_point(0, 0, 0));
	q.a = pow(r.direction.x, 2) + pow(r.direction.z, 2);
	// ray is parallel to the y axis
	if (q.a < EPSILON)
		return (ft_add_caps_cy(o, r, &xs)); // test here
	q.b = 2 * r.origin.x * r.direction.x + 2 * r.origin.z * r.direction.z;
	q.c = pow(r.origin.x, 2) + pow(r.origin.z, 2) - 1;
	q.d = pow(q.b, 2) - 4 * q.a * q.c;
	if (q.d >= 0)
	{
		t = (-q.b - sqrt(q.d)) / (2 * q.a);
		if (ft_pt_bound_cy(o, r, t))
			xs = ft_xnew(o, t);
		if (q.d > 0)
		{
			t = (-q.b + sqrt(q.d)) / (2 * q.a);
			if (ft_pt_bound_cy(o, r, t))
				ft_xadd_back(&xs, ft_xnew(o, t));
		}
	}
	return (ft_add_caps_cy(o, r, &xs));
}

t_xnode	*ft_intersect_cone(t_obj *o, t_ray r)
{
	t_quadratics	q;
	t_xnode			*xs;
	double			t;

	xs = NULL;
	r = ft_transform_ray(o -> transform_inverse, r);
	q.a = pow(r.direction.x, 2) - pow(r.direction.y, 2) + pow(r.direction.z, 2);
	q.b = 2 * r.origin.x * r.direction.x - 2 * r.origin.y * r.direction.y + 2 * r.origin.z * r.direction.z;
	q.c = pow(r.origin.x, 2) - pow(r.origin.y, 2) + pow(r.origin.z, 2);
	if (ft_fequals(q.a, 0) && ft_fequals(q.b, 0))
		return (ft_add_caps_cone(o, r, &xs));
	if (ft_fequals(q.a, 0) && !ft_fequals(q.b, 0))
	{
		xs = ft_xnew(o, (-q.c) / (2 * q.b));
		return (ft_add_caps_cone(o, r, &xs));
	}
	q.d = pow(q.b, 2) - 4 * q.a * q.c;
	if (q.d >= 0)
	{
		t = (-q.b - sqrt(q.d)) / (2 * q.a);
		if (ft_pt_bound_cy(o, r, t))
			xs = ft_xnew(o, t);
		if (q.d > 0)
		{
			t = (-q.b + sqrt(q.d)) / (2 * q.a);
			if (ft_pt_bound_cy(o, r, t))
				ft_xadd_back(&xs, ft_xnew(o, t));
		}
	}
	return (ft_add_caps_cone(o, r, &xs));;
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
	else if (o -> type == OT_CYLINDER)
		return (ft_intersect_cylinder(o, r));
	else if (o -> type == OT_CONE)
		return (ft_intersect_cone(o, r));
	return (ft_intersect_sphere(o, r));
}

t_xnode	*ft_intersect_world(t_world *w, t_ray r)
{
	int			i;
	t_xnode		*xs;

	xs = NULL;
	i = 0;
	while (i < w -> num_objs)
		ft_xadd_back(&xs, ft_intersect_obj(&w->objs[i++], r));
	return (xs);
}
