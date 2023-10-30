/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelayad <abelayad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 13:57:19 by abelayad          #+#    #+#             */
/*   Updated: 2023/10/29 19:19:52 by abelayad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H

# include "minirt_types.h"

t_matrix	ft_view_transform_inverse(t_tuple from, t_tuple forward);
t_camera	ft_camera(t_camera raw_camera);
// t_ray		ft_ray_for_pixel(int x, int y, t_camera c);
t_ray	ft_ray_for_pixel(int x, int y, t_camera c,/* test*/ t_ray *ray_arr);
// void		ft_render(t_window window, t_world *w, t_camera c);
// void		ft_render(t_png_img img, t_world *w, t_camera c);
// void	ft_render(t_png_img img, t_world *w, t_camera c /* for test ->*/, int phase);
void	ft_render(t_png_img img, t_world w, t_camera c /* for test ->*/, int phase);
t_xnode		*ft_intersect_world(t_world *w, t_ray r);
uint32_t	ft_merge_colors(int r, int g, int b, int a);
void		ft_free_objs_and_tex(t_world *w);

#endif