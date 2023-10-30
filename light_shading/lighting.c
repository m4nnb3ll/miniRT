/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelayad <abelayad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 15:12:38 by abelayad          #+#    #+#             */
/*   Updated: 2023/10/29 20:07:25 by abelayad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_comps	ft_prepare_comps(t_ray r, t_xnode *hit, t_xnode *xs)
{
	t_comps	comps;

	comps.o = hit -> o;
	comps.x = hit -> x;
	comps.pt = ft_pos_on_ray(r, hit -> x);
	comps.ev = ft_negv(r.direction);
	comps.nv = ft_normal_at(hit -> o, comps.pt);
	comps.inside = false;
	if (comps.o->type != OT_PLANE && ft_dot(comps.ev, comps.nv) < 0)
	{
		comps.inside = true;
		comps.nv = ft_negv(comps.nv);
	}
	comps.over_pt = ft_add_tuples(comps.pt, ft_sclv(comps.nv, EPSILON));
	comps.under_pt = ft_sub_tuples(comps.pt, ft_sclv(comps.nv, EPSILON));
	comps.rv = ft_reflectv(r.direction, comps.nv);
	ft_get_ns(hit, xs, &comps);
	return (comps);
}

bool	ft_is_shadowed(t_world *w, t_light l, t_tuple over_pt)
{
	t_tuple	lv;
	double	distance;
	t_xnode	*hit;
	t_xnode	*world_xs;

	lv = ft_sub_tuples(l.position, over_pt);
	distance = ft_mag(lv);
	lv = ft_normalize(lv);
	world_xs = ft_intersect_world(w, ft_ray(over_pt, lv));
	hit = ft_hit(world_xs);
	if (hit && (hit->x - distance < EPSILON))
		return (ft_free_xs(&world_xs),/* free(hit), */ true);
	return (ft_free_xs(&world_xs),/* free(hit), */ false);
}

/*
	e_color(efficient);
	a_color(ambient);
	d_color(diffuse);
	s_color(specular);
*/
t_color	ft_lighting(t_world *w, t_light l, t_comps comps)
{
	t_phong		ph;
	t_material	m;

// I will try to initialize vars here
	ft_bzero(&ph, sizeof(t_phong));
	ft_bzero(&m, sizeof(t_material));

	m = comps.o -> material;
	ph.e_color = ft_multi_colors(ft_get_obj_color(&comps), l.color);
	ph.a_color = ft_color_scl(ph.e_color, m.ambient);
	if (ft_is_shadowed(w, l, comps.over_pt))
		return (ph.a_color);
	ph.lv = ft_normalize(ft_sub_tuples(l.position, comps.pt));
	ph.ldn = ft_dot(ph.lv, comps.nv);
	if (ph.ldn <= 0)
		return (ph.a_color);
	else
	{
		ph.d_color = ft_color_scl(ph.e_color, m.diffuse * ph.ldn);
		ph.rv = ft_reflectv(ft_negv(ph.lv), comps.nv);
		ph.rde = ft_dot(ph.rv, comps.ev);
		ph.spec_factor = pow(ph.rde, m.shininess);
		ph.s_color = ft_color_scl(ft_color_scl(
					l.color, ph.spec_factor * m.specular), (ph.rde > 0));
	}
	return (ft_add_colors(ph.s_color, ft_add_colors(ph.a_color, ph.d_color)));
}

// THERE IS A BUG BELOW TO CHECK LATER
t_color	ft_shade_hit(t_world *w, t_comps comps, int remaining)
{
	t_light *tmp_light;
	t_color	reflect_color;
	t_color	refract_color;
	t_color	final_color;

	final_color = g_black;
	tmp_light = w->light_lst;
	while (tmp_light)
	{
		reflect_color = ft_reflected_color(w, comps, remaining);
		refract_color = ft_refracted_color(w, comps, remaining);
		final_color = ft_add_colors(
				ft_add_colors(final_color, ft_lighting(w, *tmp_light, comps)),
				ft_add_colors(reflect_color, refract_color));
		tmp_light = tmp_light -> next;
	}
	return (final_color);
}

t_color	ft_color_at(t_world *w, t_ray r, int remaining)
{
	t_xnode	*hit;
	t_comps	comps;
	t_xnode	*world_xs;
	t_color	color;

	hit = NULL;
	world_xs = NULL;
	ft_bzero(&comps, sizeof(t_comps));
	world_xs = ft_intersect_world(w, r);
	hit = ft_hit(world_xs);
	if (hit)
	{
		comps = ft_prepare_comps(r, hit, world_xs);
		color = ft_shade_hit(w, comps, remaining);
		return (ft_free_xs(&world_xs), color);
	}
	// printf("I return black from here 3\n");
	return (ft_free_xs(&world_xs), g_black);
}
