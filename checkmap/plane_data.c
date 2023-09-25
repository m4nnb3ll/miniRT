/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelayad <abelayad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 20:41:50 by ogorfti           #+#    #+#             */
/*   Updated: 2023/09/25 13:03:24 by abelayad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

char	**fill_plane(char **split,
			t_obj *obj, t_tuple *axis_tuple, t_tuple *coords_tuple)
{
	char		**coords;
	char		**axis;
	char		**rgb;

	obj->type = OT_PLANE;
	if (nbr_info(split) != 4)
		error_msg("Error: Incomplete plane input\n");
	coords = ft_split(split[1], ',');
	axis = ft_split(split[2], ',');
	rgb = ft_split(split[3], ',');
	*coords_tuple = ft_point(my_strtod(coords[0]),
			my_strtod(coords[1]), my_strtod(coords[2]));
	*axis_tuple = ft_vector(my_strtod(axis[0]),
			my_strtod(axis[1]), my_strtod(axis[2]));
	if (nbr_info(rgb) != 3 || nbr_info(coords) != 3 || nbr_info(axis) != 3
		|| ft_mag(*axis_tuple) != 1 || check_range(*axis_tuple))
		error_msg("Error: Incomplete plane input\n");
	free_double(coords);
	free_double(axis);
	return (rgb);
}

void	plane_data(char **split, t_obj *obj)
{
	t_tuple		coords_tuple;
	t_tuple		axis_tuple;
	t_plane		*plane;
	char		**rgb;

	rgb = fill_plane(split, obj, &axis_tuple, &coords_tuple);
	plane = ft_calloc(sizeof(t_plane), 1);
	obj->props = plane;
	obj->material = ft_material();
	obj->material.color = (t_color){
		translatecolor(my_strtod(rgb[0])),
		translatecolor(my_strtod(rgb[1])),
		translatecolor(my_strtod(rgb[2]))};
	plane->pt = (t_tuple){
		coords_tuple.x, coords_tuple.y, coords_tuple.z, coords_tuple.w};
	plane->normal = (t_tuple){
		axis_tuple.x, axis_tuple.y, axis_tuple.z, axis_tuple.w};
	plane->normal = ft_normalize(plane->normal);
	obj->transform_inverse = ft_inverse(ft_multi_matrices(
				ft_translate(plane->pt.x, plane->pt.y, plane->pt.z),
				ft_get_rotation_matrix(ft_vector(0, 0, 1), plane->normal)));
	obj->btex = ft_png_img_to_btex(ft_read_png_file("normal_texture.png"));
	free_double(rgb);
}
