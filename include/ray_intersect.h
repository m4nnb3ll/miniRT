/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_intersect.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelayad <abelayad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 13:56:37 by abelayad          #+#    #+#             */
/*   Updated: 2023/09/21 11:09:43 by abelayad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_INTERSECT_H
# define RAY_INTERSECT_H

t_ray	ft_ray(t_tuple origin, t_tuple direction);
t_tuple	ft_pos_on_ray(t_ray r, double x);
t_ray	ft_transform_ray(t_matrix m, t_ray r);
bool	ft_check_cap_cy(t_ray r, double t);
bool	ft_check_cap_cone(t_ray r, double t);
t_xnode	*ft_add_caps_cy(t_obj *cy, t_ray r, t_xnode **xs);
t_xnode	*ft_add_caps_cone(t_obj *cy, t_ray r, t_xnode **xs);
t_xnode	*ft_intersect_sphere(t_obj *o, t_ray r);
t_xnode	*ft_intersect_plane(t_obj *o, t_ray r);
t_xnode	*ft_intersect_cylinder(t_obj *o, t_ray r);
t_xnode	*ft_intersect_cone(t_obj *o, t_ray r);
t_xnode	*ft_intersect_world(t_world *w, t_ray r);
bool	ft_pt_bound_cy(t_obj *o, t_ray r, double t);
bool	ft_pt_bound_cone(t_obj *o, t_ray r, double t);
t_xnode	*ft_hit(t_xnode *xlst);
void	ft_intersect_cone_xs(t_xnode **xs, t_quadratics q, t_obj *o, t_ray r);
// TEST BELOW
void	ft_free_xs(t_xnode **xs_lst);

#endif