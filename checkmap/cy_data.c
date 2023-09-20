/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cy_data.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogorfti <ogorfti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 20:46:30 by ogorfti           #+#    #+#             */
/*   Updated: 2023/09/20 20:46:53 by ogorfti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	cylinder_data(char **split, t_obj *obj)
{
	t_cylinder	*cylinder;
	t_tuple		coords_tuple;
	t_tuple		axis_tuple;
	char		**coords;
	char		**axis;
	char		**rgb;

	obj->type = OT_CYLINDER;
	if (nbr_info(split) != 6)
		error_msg("Error: Incomplete cylinder input\n");
	coords = ft_split(split[1], ',');
	axis = ft_split(split[2], ',');
	rgb = ft_split(split[5], ',');
	coords_tuple = ft_point(my_strtod(coords[0]),
			my_strtod(coords[1]), my_strtod(coords[2]));
	axis_tuple = ft_vector(my_strtod(axis[0]),
			my_strtod(axis[1]), my_strtod(axis[2]));
	if (nbr_info(rgb) != 3 || nbr_info(coords) != 3 || nbr_info(axis) != 3
		|| check_range(axis_tuple) || ft_mag(axis_tuple) != 1)
		error_msg("Error: Incomplete cylinder input\n");
	cylinder = ft_calloc(sizeof(t_cylinder), 1);
	obj->props = cylinder;
	obj->material = ft_material();
	cylinder->d = my_strtod(split[3]);
	cylinder->h = my_strtod(split[4]);
	obj->material.color = (t_color){
		translatecolor(my_strtod(rgb[0])),
		translatecolor(my_strtod(rgb[1])),
		translatecolor(my_strtod(rgb[2]))};
	cylinder->axis = (t_tuple){
		axis_tuple.x, axis_tuple.y, axis_tuple.z, axis_tuple.w};
	cylinder->center = (t_tuple){
		coords_tuple.x, coords_tuple.y, coords_tuple.z, coords_tuple.w};
	obj->transform_inverse = ft_inverse(ft_multi_matrices(ft_translate(
					cylinder->center.x, cylinder->center.y, cylinder->center.z),
				ft_multi_matrices(ft_get_rotation_matrix(
						ft_vector(0, 1, 0), cylinder->axis), 
					ft_scale(cylinder->d, cylinder->h, cylinder->d))));
	free_double(rgb);
	free_double(axis);
	free_double(coords);
}
