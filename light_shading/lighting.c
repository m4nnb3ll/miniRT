#include "minirt.h"

t_point_light	ft_point_light(t_tuple position, t_color intensity)
{
	return ((t_point_light){ position, intensity });
}

t_material	ft_material(void)
{
	return ((t_material){ g_white, .1, .9, .9, 200 });
}

t_tuple	ft_obj_normal(t_obj *o, t_tuple wp)
{
	t_tuple	op;

	if (o -> type == OT_PLANE)
		return ((t_tuple){0, 1, 0, 0});
	else
	{
		op = ft_transform_tuple(o -> transform_inverse, wp);
		return (ft_sub_tuples(op, ft_point(0, 0, 0)));
	}
}

t_tuple	ft_normal_at(t_obj *o, t_tuple wp)
{
	t_tuple		on, wn;

	on = ft_obj_normal(o, wp);
	wn = ft_transform_tuple(ft_transpose(o -> transform_inverse), on);
	wn.w = 0;
	return (ft_normalize(wn));
}

t_tuple	ft_reflectv(t_tuple in, t_tuple n)
{
	return (ft_sub_tuples(in, ft_sclv(n, 2 * ft_dot(in, n))));
}

t_comps	ft_prepare_comps(t_ray r, t_xnode *hit)
{
	t_comps	comps;

	comps.o = hit -> o;
	comps.x = hit -> x;
	comps.pt = ft_pos_on_ray(r, hit -> x);
	comps.ev = ft_negv(r.direction);
	comps.nv = ft_normal_at(hit -> o, comps.pt);
	comps.inside = false;
	if (ft_dot(comps.ev, comps.nv) < 0)
	{
		comps.inside = true;
		comps.nv = ft_negv(comps.nv);
	}
	comps.over_pt = ft_add_tuples(comps.pt, ft_sclv(comps.nv, EPSILON));
	return (comps);
}

bool	ft_is_shadowed(t_world w, t_tuple over_pt)
{
	(void)w;
	(void)over_pt;
	t_tuple	lv;
	double	distance;
	t_xnode	*hit;

	lv = ft_sub_tuples(w.light.position, over_pt);
	distance = ft_mag(lv);
	lv = ft_normalize(lv);
	hit = ft_hit(ft_intersect_world(w, ft_ray(over_pt, lv)));
	if (hit && (hit->x - distance < EPSILON))
		return (true);
	return (false);
}

/*
	e_color(efficient);
	a_color(ambient);
	d_color(diffuse);
	s_color(specular);
*/
t_color	ft_lighting(t_world w, t_comps comps)
{
	t_phong			ph;
	t_material	m;

	m = comps.o -> material;
	ph.e_color = ft_multi_colors(m.color, w.light.intensity);
	ph.a_color = ft_color_scl(ph.e_color, m.ambient);
	if (ft_is_shadowed(w, comps.over_pt))
		return (ph.a_color);
	ph.lv = ft_normalize(ft_sub_tuples(w.light.position, comps.pt));
	ph.ldn = ft_dot(ph.lv, comps.nv);
	if (ph.ldn <= 0)
		return (ph.a_color);
	else
	{
		ph.d_color = ft_color_scl(ph.e_color, m.diffuse * ph.ldn);
		ph.rv = ft_reflectv(ft_negv(ph.lv), comps.nv);
		ph.rde = ft_dot(ph.rv, comps.ev);
		if (ph.rde <= 0)
			ph.s_color = g_black;
		else
		{
			ph.spec_factor = pow(ph.rde, m.shininess);
			ph.s_color = ft_color_scl(w.light.intensity, ph.spec_factor * m.specular);
		}
	}
	return (ft_add_colors(ph.s_color, ft_add_colors(ph.a_color, ph.d_color)));
}

t_color	ft_shade_hit(t_world w, t_comps comps)
{
	return (ft_lighting( w, comps ));
}

t_color	ft_color_at(t_world w, t_ray r)
{
	t_xnode	*hit;
	t_comps	comps;

	hit = ft_hit(ft_intersect_world(w, r));
	if (hit)
	{
		comps = ft_prepare_comps(r, hit);
		return (ft_shade_hit(w, comps));
	}
	return (g_black);
}