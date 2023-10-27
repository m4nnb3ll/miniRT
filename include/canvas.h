/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canvas.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelayad <abelayad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 13:43:10 by abelayad          #+#    #+#             */
/*   Updated: 2023/10/25 22:16:28 by abelayad         ###   ########.fr       */
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
void		ft_print_color(t_color c);
// t_window	ft_img_ptr(void);
void		ft_free_tex(t_tex tex);
t_color		ft_tex_color_at(t_comps *comps);

#endif