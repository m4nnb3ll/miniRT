/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogorfti <ogorfti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 20:45:30 by ogorfti           #+#    #+#             */
/*   Updated: 2023/09/20 22:16:55 by ogorfti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	cone_data(char **split, t_obj *obj)
{
	t_cone		*cone;
	t_tuple		coords_tuple;
	t_tuple		axis_tuple;
	char		**coords;
	char		**axis;
	char		**rgb;

	obj->type = OT_CONE;
	if (nbr_info(split) != 6)
		error_msg("Error: Incomplete cone input\n");
	coords = ft_split(split[1], ',');
	axis = ft_split(split[2], ',');
	rgb = ft_split(split[5], ',');
	coords_tuple = ft_point(my_strtod(coords[0]),
			my_strtod(coords[1]), my_strtod(coords[2]));
	axis_tuple = ft_vector(my_strtod(axis[0]),
			my_strtod(axis[1]), my_strtod(axis[2]));
	if (nbr_info(rgb) != 3 || nbr_info(coords) != 3 || nbr_info(axis) != 3
		|| check_range(axis_tuple) || ft_mag(axis_tuple) != 1)
		error_msg("Error: Incomplete cone input\n");
	cone = ft_calloc(sizeof(t_cone), 1);
	obj->props = cone;
	obj->material = ft_material();
	cone->d = my_strtod(split[3]);
	cone->h = my_strtod(split[4]);
	obj->material.color = (t_color){
		translatecolor(my_strtod(rgb[0])),
		translatecolor(my_strtod(rgb[1])),
		translatecolor(my_strtod(rgb[2]))
	};
	cone->axis = (t_tuple){
		axis_tuple.x, axis_tuple.y, axis_tuple.z, axis_tuple.w};
	cone->center = (t_tuple){
		coords_tuple.x, coords_tuple.y, coords_tuple.z, coords_tuple.w};
	obj->transform_inverse = ft_inverse(ft_multi_matrices(ft_translate(
					cone->center.x, cone->center.y, cone->center.z),
				ft_multi_matrices(ft_get_rotation_matrix(
						ft_vector(0, 1, 0), cone->axis),
					ft_scale(cone->d, cone->h, cone->d))));
	free_double(rgb);
	free_double(axis);
	free_double(coords);
}
