/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quaternions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelayad <abelayad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 15:30:55 by abelayad          #+#    #+#             */
/*   Updated: 2023/09/20 17:40:00 by abelayad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "libft.h"

t_tuple	ft_get_quat(t_tuple rot_axe, double radian)
{
	double	sine;

	radian /= 2;
	sine = sin(radian);
	return ((t_tuple){
		cos(radian),
		rot_axe.x * sine,
		rot_axe.y * sine,
		rot_axe.z * sine
	});
}

t_matrix	ft_quat_to_matrix(t_tuple q)
{
	return ((t_matrix){4, {
			{
				1 - 2 * (pow(q.z, 2) + pow(q.w, 2)),
				2 * (q.y * q.z - q.x * q.w),
				2 * (q.y * q.w + q.x * q.z),
				0
			},
			{
				2 * (q.y * q.z + q.x * q.w),
				1 - 2 * (pow(q.y, 2) + pow(q.w, 2)),
				2 * (q.z * q.w - q.x * q.y),
				0
			},
			{
				2 * (q.y * q.w - q.x * q.z),
				2 * (q.z * q.w + q.x * q.y),
				1 - 2 * (pow(q.y, 2) + pow(q.z, 2)),
				0
			},
			{0, 0, 0, 1}
		}});
}

// v1, v2 should both be normalized
t_matrix	ft_get_rotation_matrix(t_tuple v1, t_tuple v2)
{
	double	dot;
	double	deg_r;
	t_tuple	rot_axe;
	t_tuple	q;

	dot = ft_dot(v1, v2);
	if (ft_fequals(fabs(dot), 1))
		return (ft_matrix_scl(g_identity_matrix, dot));
	rot_axe = ft_normalize(ft_cross(v1, v2));
	deg_r = acos(dot);
	q = ft_get_quat(rot_axe, deg_r);
	return (ft_quat_to_matrix(q));
}
