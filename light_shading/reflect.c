/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflect.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelayad <abelayad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 12:29:32 by abelayad          #+#    #+#             */
/*   Updated: 2023/12/04 12:29:33 by abelayad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color	ft_reflected_color(t_world *w, t_comps c, int remaining)
{
	t_ray	reflect_ray;
	t_color	color;

	ft_bzero(&reflect_ray, sizeof(t_ray));
	ft_bzero(&color, sizeof(t_color));
	if (!c.o->material.reflective || remaining <= 0)
		return (g_black);
	reflect_ray = ft_ray(c.over_pt, c.rv);
	color = ft_color_at(w, reflect_ray, remaining - 1);
	return (ft_color_scl(color, c.o->material.reflective));
}
