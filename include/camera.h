/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelayad <abelayad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 13:57:19 by abelayad          #+#    #+#             */
/*   Updated: 2023/12/03 22:23:34 by abelayad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H

# include "minirt_types.h"

t_matrix	ft_view_transform_inverse(t_tuple from, t_tuple forward);
t_camera	ft_camera(t_camera raw_camera);
void		ft_render(t_png_img *img, t_world *w, int phase);
t_xnode		*ft_intersect_world(t_world *w, t_ray r);
void		free_world(t_world *w);

#endif