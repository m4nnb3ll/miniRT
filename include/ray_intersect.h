#ifndef RAY_INTERSECT_H
# define RAY_INTERSECT_H

void		ft_print_ray(t_ray r);
t_ray		ft_ray(t_tuple origin, t_tuple direction);
t_ray		ft_transform_ray(t_matrix m, t_ray r);
t_xnode		*ft_intersect_sphere(t_obj *o, t_ray r);
t_xnode		*ft_intersect_plane(t_obj *o, t_ray r);
t_xnode		*ft_intersect_cylinder(t_obj *o, t_ray r);
t_xnode		*ft_intersect_cone(t_obj *o, t_ray r);
t_tuple		ft_pos_on_ray(t_ray r, double x);
t_xnode		*ft_hit(t_xnode *xlst);

#endif