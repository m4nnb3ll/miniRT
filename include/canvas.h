/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canvas.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelayad <abelayad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 13:43:10 by abelayad          #+#    #+#             */
/*   Updated: 2023/09/25 12:48:26 by abelayad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CANVAS_H
# define CANVAS_H

# include "minirt_types.h"

t_color		ft_color(double r, double g, double b);
t_color		ft_add_colors(t_color a, t_color b);
t_color		ft_sub_colors(t_color a, t_color b);
t_color		ft_color_scl(t_color c, double scaler);
t_color		ft_multi_colors(t_color a, t_color b);
uint8_t		ft_255channel(double c);
// t_window	ft_img_ptr(void);
void		ft_free_btex(t_btex btex);

#endif