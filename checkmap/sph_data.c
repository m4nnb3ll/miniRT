/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sph_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelayad <abelayad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 20:06:26 by ogorfti           #+#    #+#             */
/*   Updated: 2023/09/26 22:31:36 by abelayad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	set_sphere_data(t_obj *obj, char **rgb, char **coords, char **split)
{
	t_sphere	*sphere;
	t_tuple		tuple;

	sphere = ft_calloc(1, sizeof(t_sphere));
	obj->props = sphere;
	obj->material = ft_material();
	sphere->d = my_strtod(split[2]);
	tuple = ft_point(my_strtod(coords[0]), my_strtod(coords[1]),
			my_strtod(coords[2]));
	sphere->pt = (t_tuple){
		tuple.x, tuple.y, tuple.z, tuple.w};
	obj->transform_inverse = ft_inverse(ft_multi_matrices(
				ft_translate(sphere->pt.x, sphere->pt.y, sphere->pt.z),
				ft_scale(sphere->d, sphere->d, sphere->d)));
	obj->material.color = (t_color){
		translatecolor(my_strtod(rgb[0])),
		translatecolor(my_strtod(rgb[1])),
		translatecolor(my_strtod(rgb[2]))};
}

void	sphere_data(char **split, t_obj *obj)
{
	char		**coords;
	char		**rgb;

	obj->type = OT_SPHERE;
	if (nbr_info(split) != 4)
		error_msg("Error: Incomplete sphere input\n");
	rgb = ft_split(split[3], ',');
	coords = ft_split(split[1], ',');
	if (nbr_info(rgb) != 3 || nbr_info(coords) != 3)
		error_msg("Error: Incomplete sphere input\n");
	set_sphere_data(obj, rgb, coords, split);
	free_double(rgb);
	free_double(coords);
}
