/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_shading.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelayad <abelayad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 13:44:28 by abelayad          #+#    #+#             */
/*   Updated: 2023/12/03 22:55:40 by abelayad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHT_SHADING_H
# define LIGHT_SHADING_H

t_material	ft_material(void);
t_tuple		ft_reflectv(t_tuple in, t_tuple n);
t_comps		ft_prepare_comps(t_ray r, t_xnode *hit, t_xnode *xs);
bool		ft_is_shadowed(t_world *w, t_light l, t_tuple over_pt);
t_color		ft_lighting(t_world *w, t_light l, t_comps comps);
t_color		ft_reflected_color(t_world *w, t_comps c, int remaining);
t_color		ft_refracted_color(t_world *w, t_comps comps, int remaining);
t_color		ft_shade_hit(t_world *w, t_comps comps, int remaining);
t_color		ft_color_at(t_world *w, t_ray r, int remaining);
t_tuple		ft_get_pl_normal(t_obj *pl, t_tuple op);
t_tuple		ft_obj_normal(t_obj *o, t_tuple wp);
t_tuple		ft_normal_at(t_obj *o, t_tuple wp);
t_color		ft_uv_pattern_at(t_tex texture, double u, double v);
t_tuple		ft_planar_map(t_tuple op);
void		ft_get_ns(t_xnode *hit, t_xnode *xs, t_comps *comps);
t_tuple		ft_get_sp_normal(t_obj *sp, t_tuple op);
t_tuple		ft_get_cy_normal(t_tuple op);
t_tuple		ft_get_cn_normal(t_tuple op);
t_color		ft_checkers(t_obj *o, t_tuple pt);
t_color		ft_tex_color_pl(t_comps *c);
t_color		ft_tex_color_sp(t_comps *c);
t_color		ft_tex_color_cy(t_comps *c);
t_color		ft_tex_color_at(t_comps *comps);
t_color		ft_get_obj_color(t_comps *comps);
t_tuple		ft_spherical_map(t_tuple op);
t_tuple		ft_cylinderical_map(t_tuple op);

#endif