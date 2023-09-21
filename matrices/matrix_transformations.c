/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_transformations.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelayad <abelayad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 15:30:40 by abelayad          #+#    #+#             */
/*   Updated: 2023/09/20 15:30:41 by abelayad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_matrix	ft_translate(double x, double y, double z)
{
	return ((t_matrix){
		4, {
			{1, 0, 0, x},
			{0, 1, 0, y},
			{0, 0, 1, z},
			{0, 0, 0, 1}
		}
	});
}

t_matrix	ft_scale(double x, double y, double z)
{
	return ((t_matrix){
		4, {
			{x, 0, 0, 0},
			{0, y, 0, 0},
			{0, 0, z, 0},
			{0, 0, 0, 1}
		}
	});
}

t_matrix	ft_rotate_x(double rad)
{
	return ((t_matrix){
		4, {
			{1, 0, 0, 0},
			{0, cos(rad), -sin(rad), 0},
			{0, sin(rad), cos(rad), 0},
			{0, 0, 0, 1}
		}
	});
}

t_matrix	ft_rotate_y(double rad)
{
	return ((t_matrix){
		4, {
			{cos(rad), 0, sin(rad), 0},
			{0, 1, 0, 0},
			{-sin(rad), 0, cos(rad), 0},
			{0, 0, 0, 1}
		}
	});
}

t_matrix	ft_rotate_z(double rad)
{
	return ((t_matrix){
		4, {
			{cos(rad), -sin(rad), 0, 0},
			{sin(rad), cos(rad), 0, 0},
			{0, 0, 1, 0},
			{0, 0, 0, 1}
		}
	});
}
