/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelayad <abelayad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 11:36:03 by abelayad          #+#    #+#             */
/*   Updated: 2023/09/27 13:28:48 by abelayad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	ft_print_tuple(t_tuple t)
{
	printf("%f %f %f %f\n", t.x, t.y, t.z, t.w);
}

void	ft_print_color(t_color c)
{
	printf("%f %f %f\n", c.r, c.g, c.b);
}

void	ft_print_ray(t_ray r)
{
	printf("origin: ");
	ft_print_tuple(r.origin);
	printf("direction: ");
	ft_print_tuple(r.direction);
}

void	ft_print_xs(t_xnode *xs)
{
	while (xs)
	{
		printf("%f\n", xs->x);
		xs = xs -> next;
	}
}
