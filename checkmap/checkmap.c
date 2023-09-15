/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkmap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogorfti <ogorfti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 17:34:38 by ogorfti           #+#    #+#             */
/*   Updated: 2023/09/15 20:27:20 by ogorfti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"
#include <fcntl.h>
#include <stdio.h>


void	ambient_data(char **split, t_ambient *ambient)
{
	char	**rgb;
	double	ratio;

	if (nbr_info(split, 3))
		error_msg("Error: Incomplete ambient lightning input\n");
	ratio = my_strtod(split[1]);
	if (ratio < 0 || ratio > 1)
		error_msg("Error: Invalid lightning ratio value\n");
		
	ambient->ratio = ratio;
	rgb = ft_split(split[2], ',');
	if (nbr_info(rgb, 3))
		error_msg("Error: Incomplete color input\n");

	ambient->color.r = translatecolor(my_strtod(rgb[0]));
	ambient->color.g = translatecolor(my_strtod(rgb[1]));
	ambient->color.b = translatecolor(my_strtod(rgb[2]));
	free_double(rgb);
}

void	camera_data(char **split, t_camera1 *camera)
{
	char	**vector;
	char	**coords;
	t_tuple	forward;
	t_tuple	tuple;
	double	degree;

	if (nbr_info(split, 4))
		error_msg("Error: Incomplete camera input\n");

	degree = my_strtod(split[3]);
	if (degree < 0 || degree > 180)
		error_msg("Error: Invalid camera FOV value\n");
	camera->fov = degree * (3.14 / 180.0);
	// printf("fov : %f\n", camera->fov);
	
	vector = ft_split(split[2], ',');
	coords = ft_split(split[1], ',');
	
	if (nbr_info(coords, 3) || nbr_info(vector, 3))
		error_msg("Error: Incomplete camera input\n");

	tuple = ft_point(my_strtod(coords[0]), my_strtod(coords[1]), my_strtod(coords[2]));
	camera->position.x = tuple.x;
	camera->position.y = tuple.y;
	camera->position.z = tuple.z;
	camera->position.w = tuple.w;

	forward = ft_vector(my_strtod(vector[0]), my_strtod(vector[1]), my_strtod(vector[2]));
	camera->forward_v.x = forward.x;
	camera->forward_v.y = forward.y;
	camera->forward_v.z = forward.z;
	camera->forward_v.w = forward.w;

	free_double(coords);
	free_double(vector);
}

void	light_data(char **split, t_light *light)
{
	char	**coords;
	char	**rgb;
	t_tuple	points;
	double	bright;

	if (nbr_info(split, 4))
		error_msg("Error: Incomplete light input\n");

	bright = my_strtod(split[2]);
	if (bright < 0 || bright > 1)
		error_msg("Error: Invalid light brightness value\n");
	light->brightness = bright;


	rgb = ft_split(split[3], ',');
	coords = ft_split(split[1], ',');
	if (nbr_info(rgb, 3) || nbr_info(coords, 3))
		error_msg("Error: Incomplete light input\n");

	light->color.r = translatecolor(my_strtod(rgb[0]));
	light->color.g = translatecolor(my_strtod(rgb[1]));
	light->color.b = translatecolor(my_strtod(rgb[2]));
	
	points = ft_point(my_strtod(coords[0]), my_strtod(coords[1]), my_strtod(coords[2]));
	light->position.x = points.x;
	light->position.y = points.y;
	light->position.z = points.z;
	light->position.w = points.w;

	free_double(rgb);
	free_double(coords);
}

void	sphere_data(char **split, t_obj1 *obj)
{
	t_sphere	*sphere;
	t_tuple		tuple;
	char		**coords;
	char		**rgb;

	obj->type = OT_SPHERE;
	if (nbr_info(split, 4))
		error_msg("Error: Incomplete sphere input\n");


	rgb = ft_split(split[3], ',');
	coords = ft_split(split[1], ',');
	if (nbr_info(rgb, 3) || nbr_info(coords, 3))
		error_msg("Error: Incomplete sphere input\n");

	sphere = malloc(sizeof(t_sphere));
	obj->props = sphere;
	if (!sphere)
		exit(1);

	sphere->diameter = my_strtod(split[2]);
	tuple = ft_point(my_strtod(coords[0]), my_strtod(coords[1]), my_strtod(coords[2]));

	sphere->position.x = tuple.x;
	sphere->position.y = tuple.y;
	sphere->position.z = tuple.z;
	sphere->position.w = tuple.z;

	obj->material.color.r = translatecolor(my_strtod(rgb[0]));
	obj->material.color.g = translatecolor(my_strtod(rgb[1]));
	obj->material.color.b = translatecolor(my_strtod(rgb[2]));

	free_double(rgb);
	free_double(coords);
}

void	plane_data(char **split, t_obj1 *obj)
{
	t_tuple		coords_tuple;
	t_tuple		axis_tuple;
	t_plane1	*plane;
	char		**coords;
	char		**axis;
	char		**rgb;

	obj->type = OT_PLANE;
	if (nbr_info(split, 4))
		error_msg("Error: Incomplete plane input\n");
	
	coords = ft_split(split[1], ',');
	axis = ft_split(split[2], ',');
	rgb = ft_split(split[3], ',');
	
	coords_tuple = ft_point(my_strtod(coords[0]), my_strtod(coords[1]), my_strtod(coords[2]));
	axis_tuple = ft_vector(my_strtod(axis[0]), my_strtod(axis[1]), my_strtod(axis[2]));
	
	if (nbr_info(rgb, 3) || nbr_info(coords, 3) || nbr_info(axis, 3) || ft_mag(axis_tuple) != 1 || check_range(axis_tuple))
		error_msg("Error: Incomplete plane input\n");

	obj->material.color.r = translatecolor(my_strtod(rgb[0]));
	obj->material.color.g = translatecolor(my_strtod(rgb[1]));
	obj->material.color.b = translatecolor(my_strtod(rgb[2]));

	plane = malloc(sizeof(t_plane1));
	if (!plane)
		exit(1);
	obj->props = plane;
	plane->position.x = coords_tuple.x;
	plane->position.y = coords_tuple.y;
	plane->position.z = coords_tuple.z;
	plane->position.w = coords_tuple.w;

	plane->normal.x = axis_tuple.x;
	plane->normal.y = axis_tuple.y;
	plane->normal.z = axis_tuple.z;
	plane->normal.w = axis_tuple.w;
	
	free_double(rgb);
	free_double(axis);
	free_double(coords);
}

void	cylinder_data(char **split, t_obj1 *obj)
{
	t_cylinder	*cylinder;
	t_tuple		coords_tuple;
	t_tuple		axis_tuple;
	char		**coords;
	char		**axis;
	char		**rgb;

	obj->type = 13;
	if (nbr_info(split, 6))
		error_msg("Error: Incomplete cylinder input\n");
	
	coords = ft_split(split[1], ',');
	axis = ft_split(split[2], ',');
	rgb = ft_split(split[5], ',');
	
	coords_tuple = ft_point(my_strtod(coords[0]), my_strtod(coords[1]), my_strtod(coords[2]));
	axis_tuple = ft_vector(my_strtod(axis[0]), my_strtod(axis[1]), my_strtod(axis[2]));
	
	if (nbr_info(rgb, 3) || nbr_info(coords, 3) || nbr_info(axis, 3) || check_range(axis_tuple) || ft_mag(axis_tuple) != 1)
		error_msg("Error: Incomplete cylinder input\n");
	
	cylinder = malloc(sizeof(t_cylinder));
	obj->props = cylinder;
	cylinder->diameter = my_strtod(split[3]);
	cylinder->height = my_strtod(split[4]);
	
	obj->material.color.r = translatecolor(my_strtod(rgb[0]));
	obj->material.color.g = translatecolor(my_strtod(rgb[1]));
	obj->material.color.b = translatecolor(my_strtod(rgb[2]));

	cylinder->axis.x = axis_tuple.x;
	cylinder->axis.y = axis_tuple.y;
	cylinder->axis.z = axis_tuple.z;
	cylinder->axis.w = axis_tuple.w;

	cylinder->center.x = coords_tuple.x;
	cylinder->center.y = coords_tuple.y;
	cylinder->center.z = coords_tuple.z;
	cylinder->center.w = coords_tuple.w;

	free_double(rgb);
	free_double(axis);
	free_double(coords);
}

void	objs_data(char **split, t_obj1 *obj)
{
	if (ft_strcmp(split[0], "cy") == 0)
		cylinder_data(split, obj);
	else if (ft_strcmp(split[0], "sp") == 0)
		sphere_data(split, obj);
	else
		plane_data(split, obj);
}

void	free_struct(t_find *find)
{
	int i;

	i = 0;
	while (find[i].split)
	{
		free_double(find[i].split);
		i++;
	}
	free(find);
}

t_world1	*fill_data(t_data *data)
{
	t_world1 *world;
	char	**split;
	int j;
	int	i;

	i = 0;
	j = 0;
	world = ft_calloc(sizeof(t_world1), 1);
	world->nbr_obj = calculate_objs(data);
	world->objects = ft_calloc(sizeof(t_obj1) , world->nbr_obj);
	while (data->find[i].split)
	{
		split = &data->find[i].split[0];
		if (split[0] && !ft_strcmp(split[0], "A"))
		{
			// printf("A id a detected\n");
			ambient_data(data->find[i].split, &world->ambient);
		}
		else if (split[0] && !ft_strcmp(split[0], "C"))
		{
			// printf("C id a detected\n");
			camera_data(data->find[i].split, &world->camera);
		}
		else if (split[0] && !ft_strcmp(split[0], "L"))
		{
			// printf("L id a detected\n");
			light_data(data->find[i].split, &world->light);
		}
		else if (split[0] && (!ft_strcmp(split[0], "pl") || !ft_strcmp(split[0], "sp") || !ft_strcmp(split[0], "cy")))
		{
			// printf("obj id a detected\n");
			objs_data(split, world->objects + j);
			j++;
		}
		else
			error_msg("Invalid input\n");
		i++;
	}
	free_double(data->map);
	free_struct(data->find);
	// 'world' struct and 'world->objects' should be freed after they have finished their job.
	return (world);
}

//call world_data function to get all data (filename is av[1])
t_world1	*world_data(char *filename)
{
	t_world1	*world;
	t_data		data;

	// check name function should be here
	allocate_map(filename, &data);
	split_data(&data);
	world = fill_data(&data);
	return (world);
}

// int main()
// {
// 	t_world1 *world = world_data("../artwork/test.rt");
// 	t_sphere *test = world->objects[1].props;
// 	printf("---------------> %.1f\n", test->diameter);
// 	printf("---------------> %.2f\n", world->camera.fov);
// }




