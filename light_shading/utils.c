/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelayad <abelayad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 15:12:44 by abelayad          #+#    #+#             */
/*   Updated: 2023/10/24 15:20:25 by abelayad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
typedef struct s_material
{
	t_color	color;
	double	ambient;
	double	diffuse;
	double	specular;
	double	shininess;
	double	reflective; // [0.0-1.0]
	double	transparency;
	double	ri;// refractive index
}	t_material;
*/

t_material	ft_material(void)
{
	return ((t_material){g_white, .1, .7, .2, 200, 0, 0, GLASS});
}

t_tuple	ft_reflectv(t_tuple in, t_tuple n)
{
	return (ft_sub_tuples(in, ft_sclv(n, 2 * ft_dot(in, n))));
}

t_color	ft_checkers(t_objnode *o, t_tuple pt)
{
	t_tuple	op;

	op = ft_transform_tuple(o->transform_inverse, pt);
	if ((int)(fabs(floor(op.x)) + fabs(floor(op.y))) % 2 == 0)
	{
		// printf("I return black from here 4\n");
		return (g_black);
	}
	return (o->material.color);
}

t_color	ft_get_obj_color(t_comps *comps)
{
	// if (comps -> o -> type == OT_PLANE)
	// 	return (ft_checkers(comps->o, comps->pt));
	return (comps -> o -> material.color);
}
