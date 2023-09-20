/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelayad <abelayad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 13:57:19 by abelayad          #+#    #+#             */
/*   Updated: 2023/09/20 13:57:22 by abelayad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "minirt_types.h"

t_matrix	ft_view_transform_inverse(t_tuple from, t_tuple forward);
t_camera	ft_camera(t_camera raw_camera);
t_ray		ft_ray_for_pixel(int x, int y, t_camera c);
void		ft_render(t_window window, t_world *w, t_camera c);
t_xnode		*ft_intersect_world(t_world *w, t_ray r);

#endif