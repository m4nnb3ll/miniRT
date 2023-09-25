/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelayad <abelayad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 12:52:29 by abelayad          #+#    #+#             */
/*   Updated: 2023/09/25 12:37:10 by abelayad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

const t_color	g_black = (t_color){0.1, 0.1, 0.1};
const t_color	g_white = (t_color){1, 1, 1};
const t_color	g_red = (t_color){1, 0, 0};
const t_color	g_green = (t_color){0, 1, 0};
const t_color	g_blue = (t_color){0, 0, 1};

t_color	ft_color(double r, double g, double b)
{
	return ((t_color){r, g, b});
}

t_color	ft_add_colors(t_color a, t_color b)
{
	return ((t_color){
		a.r + b.r,
		a.g + b.g,
		a.b + b.b
	});
}

t_color	ft_sub_colors(t_color a, t_color b)
{
	return ((t_color){
		a.r - b.r,
		a.g - b.g,
		a.b - b.b
	});
}

t_color	ft_color_scl(t_color c, double scaler)
{
	return ((t_color){
		c.r * scaler,
		c.g * scaler,
		c.b * scaler
	});
}

t_color	ft_multi_colors(t_color a, t_color b)
{
	return ((t_color){
		a.r * b.r,
		a.g * b.g,
		a.b * b.b
	});
}
