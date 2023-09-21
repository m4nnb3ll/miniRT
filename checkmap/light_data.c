/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogorfti <ogorfti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 18:46:55 by ogorfti           #+#    #+#             */
/*   Updated: 2023/09/20 20:04:51 by ogorfti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	set_rgb(char **split, t_light *light)
{
	char	**rgb;

	rgb = 0;
	if (nbr_info(split) == 4)
	{
		rgb = ft_split(split[3], ',');
		if (nbr_info(rgb) != 3)
			error_msg("Error: Incomplete color input\n");
	}
	if (rgb)
	{
		light->color = (t_color){
			translatecolor(my_strtod(rgb[0])),
			translatecolor(my_strtod(rgb[1])),
			translatecolor(my_strtod(rgb[2]))};
	}
	free_double(rgb);
}

void	light_data(char **split, t_light *light)
{
	char	**coords;
	t_tuple	points;
	double	bright;

	if (!(nbr_info(split) >= 3 && nbr_info(split) <= 4))
		error_msg("Error: Incomplete light input\n");
	bright = my_strtod(split[2]);
	if (bright < 0 || bright > 1)
		error_msg("Error: Invalid light brightness value\n");
	set_rgb(split, light);
	light->brightness = bright;
	coords = ft_split(split[1], ',');
	if (nbr_info(coords) != 3)
		error_msg("Error: Incomplete light input\n");
	points = ft_point(my_strtod(coords[0]),
			my_strtod(coords[1]), my_strtod(coords[2]));
	light->position = (t_tuple){
		points.x, points.y, points.z, points.w};
	free_double(coords);
}
