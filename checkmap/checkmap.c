/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkmap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelayad <abelayad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 17:34:38 by ogorfti           #+#    #+#             */
/*   Updated: 2023/09/28 11:54:35 by abelayad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	objs_data(char **split, t_objnode *obj)
{
	if (ft_strcmp(split[0], "cy") == 0)
		cylinder_data(split, obj);
	else if (ft_strcmp(split[0], "sp") == 0)
		sphere_data(split, obj);
	else if (ft_strcmp(split[0], "cn") == 0)
		cone_data(split, obj);
	else
		plane_data(split, obj);
}

void	init_world(t_data *data, t_world *world, int *i, int *j)
{
	*i = 0;
	*j = 0;
	check_count(data);
	world->num_lights = 0; 
	world->num_objs = calculate_objs(data);
	world->objs = ft_calloc(sizeof(t_objnode), world->num_objs);
}

void	fill_data(t_world *world, t_data *data)
{
	char	**split;
	int		j;
	int		i;

	init_world(data, world, &i, &j);
	while (data->find[i].split)
	{
		split = &data->find[i].split[0];
		if (split[0] && !ft_strcmp(split[0], "A"))
			ambient_data(data->find[i].split, &world->ambient);
		else if (split[0] && !ft_strcmp(split[0], "C"))
			camera_data(data->find[i].split, &world->camera);
		else if (split[0] && (!ft_strcmp(split[0], "L")
				|| !ft_strcmp(split[0], "l")))
		{
			light_data(data->find[i].split, &world->lights[world->num_lights]);
			world->num_lights++;
		}
		else if (split[0])
		{
			objs_data(split, world->objs + j);
			j++;
		}
		i++;
	}
}

void	world_data(t_world *world, char *filename)
{
	t_data		data;

	if (check_name(filename))
		error_msg("Invalid file name!\n");
	allocate_map(filename, &data);
	split_data(&data);
	fill_data(world, &data);
	free_double(data.map);
	free_struct(data.find);
}
