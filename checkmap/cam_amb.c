/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam_amb.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelayad <abelayad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 21:02:08 by ogorfti           #+#    #+#             */
/*   Updated: 2023/09/26 16:09:51 by abelayad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	ambient_data(char **split, t_ambient *ambient)
{
	double	ratio;
	char	**rgb;

	if (nbr_info(split) != 3)
		error_msg("Error: Incomplete ambient lightning input\n");
	ratio = my_strtod(split[1]);
	if (ratio < 0 || ratio > 1)
		error_msg("Error: Invalid lightning ratio value\n");
	ambient->ratio = ratio;
	rgb = ft_split(split[2], ',');
	if (nbr_info(rgb) != 3)
		error_msg("Error: Incomplete color input\n");
	ambient->color = (t_color){
		translatecolor(my_strtod(rgb[0])),
		translatecolor(my_strtod(rgb[1])),
		translatecolor(my_strtod(rgb[2]))};
	free_double(rgb);
}

void	camera_data(char **split, t_camera *camera)
{
	char	**vector;
	char	**coords;
	double	degree;
	t_tuple	fov;

	if (nbr_info(split) != 4)
		error_msg("Error: Incomplete camera input\n");
	degree = my_strtod(split[3]);
	if (degree < 0 || degree > 180)
		error_msg("Error: Invalid camera FOV value\n");
	camera->fov = degree * (PI / 180);
	vector = ft_split(split[2], ',');
	coords = ft_split(split[1], ',');
	if (nbr_info(coords) != 3 || nbr_info(vector) != 3)
		error_msg("Error: Incomplete camera input\n");
	camera->from = ft_point(
			my_strtod(coords[0]), my_strtod(coords[1]), my_strtod(coords[2]));
	fov = ft_vector(
			my_strtod(vector[0]), my_strtod(vector[1]), my_strtod(vector[2]));
	if (!ft_fequals(ft_mag(fov), 1))
		error_msg("Error: Incomplete camera input --\n");
	else
		camera->to = fov;
	free_double(coords);
	free_double(vector);
}
