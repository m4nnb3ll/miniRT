#ifndef LIGHT_SHADING_H
# define LIGHT_SHADING_H

t_tuple				ft_normal_at(t_objnode *o, t_tuple p);
t_point_light	ft_point_light(t_tuple position, t_color intensity);
t_material		ft_material(void);
t_tuple				ft_reflectv(t_tuple in, t_tuple n);
t_color				ft_lighting(t_world w, t_comps comps);
t_comps				ft_prepare_comps(t_ray r, t_xnode *hit);
t_color				ft_shade_hit(t_world w, t_comps comps);
t_color				ft_color_at(t_world w, t_ray r);
bool				ft_is_shadowed(t_world w, t_tuple over_pt);

#endif