/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogorfti <ogorfti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 17:34:38 by ogorfti           #+#    #+#             */
/*   Updated: 2023/09/13 20:52:23 by ogorfti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../include/minirt.h"
#include <fcntl.h>
#include <stdio.h>

void	display_map(char **map)
{
	int i;

	i = 0;
	while (map[i])
	{
		printf("%s\n", map[i]);
		i++;
	}
}

int ft_strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
    while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
    return (s1[i] -s2[i]);
}

void	error_msg(char *str)
{
	ft_putstr_fd(str, 1);
	exit (1);
}

void	allocate_map(char *file, t_data *data)
{
	char	*joiner;
	char	*line;
	int		fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		error_msg("Error: File open failed.\n");
	joiner = ft_calloc(1, 1);
	data->mapsize = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		joiner = ft_strjoin(joiner, line);
		if (ft_strncmp(line, "\n", ft_strlen(line)))
			data->mapsize++;
		free (line);
	}
	data->map = ft_split(joiner, '\n');
	free (joiner);
}

void	split_data(t_data *data)
{
	int i;

	i = 0;
	// printf("size : %d\n", data->mapsize);
	data->find = malloc(sizeof(t_find) * (data->mapsize + 1));
	while (data->map[i])
	{
		data->find[i].split = split_string(data->map[i]);
		i++;
	}
	data->find[i].split = NULL;
}

int nbr_info(char **str, int shouldbe)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	if (i != shouldbe)
		return (1);
	return (0);
}

void	ambient_data(char **split, t_ambient *ambient)
{
	char	**rgb;

	if (nbr_info(split, 3))
		error_msg("Error: Incomplete ambient lightning input\n");
	ambient->ratio = my_strtod(split[1]);


	rgb = ft_split(split[2], ',');
	if (nbr_info(rgb, 3))
		error_msg("Error: Incomplete color input\n");

	ambient->color.r = ft_atoi(rgb[0]);
	ambient->color.g = ft_atoi(rgb[1]);
	ambient->color.b = ft_atoi(rgb[2]);
}

void	camera_data(char **split, t_camera1 *camera)
{
	char	**vector;
	char	**coords;

	if (nbr_info(split, 4))
		error_msg("Error: Incomplete camera input\n");
	camera->fov = my_strtod(split[3]) * (3.14 / 180.0);
	// printf("fov : %f\n", camera->fov);
	
	vector = ft_split(split[2], ',');
	coords = ft_split(split[1], ',');
	
	if (nbr_info(coords, 3) || nbr_info(vector, 3))
		error_msg("Error: Incomplete camera input\n");

	camera->position.x = ft_atoi(coords[0]);
	camera->position.y = ft_atoi(coords[1]);
	camera->position.z = ft_atoi(coords[2]);
	camera->forward_v.x = ft_atoi(vector[0]);
	camera->forward_v.y = ft_atoi(vector[1]);
	camera->forward_v.z = ft_atoi(vector[2]);
}

void	light_data(char **split, t_light *light)
{
	char	**coords;
	char	**rgb;

	if (nbr_info(split, 4))
		error_msg("Error: Incomplete light input\n");
	
	light->brightness = my_strtod(split[2]);


	rgb = ft_split(split[3], ',');
	coords = ft_split(split[1], ',');
	if (nbr_info(rgb, 3) || nbr_info(coords, 3))
		error_msg("Error: Incomplete light input\n");

	light->color.r = ft_atoi(rgb[0]);
	light->color.g = ft_atoi(rgb[1]);
	light->color.b = ft_atoi(rgb[2]);
	
	light->position.x = ft_atoi(rgb[0]);
	light->position.y = ft_atoi(rgb[1]);
	light->position.z = ft_atoi(rgb[2]);
}

void	objs_data(char **split, t_obj1 *obj)
{
	if (ft_strcmp(split[0], "pl") == 0)
	{
		obj->type = OT_SPHERE;
		// obj->material.color;
		
		// t_sphere *sphere = (t_sphere *) obj->props;
	}
	// else if (ft_strcmp(split[0], "sp") == 0)
	// {
		
	// }
	// else if (ft_strcmp(split[0], "cy") == 0)
	// {
		
	// }
}

t_world1	*fill_data(t_data *data)
{
	t_world1 *world;
	char	**split;
	int	i;

	i = 0;
	world = malloc(sizeof(t_world1));
	while (data->find[i].split)
	{
		split = &data->find[i].split[0];
		if (split[0] && !ft_strcmp(split[0], "A"))
		{			
			printf("A id a detected\n");
			ambient_data(data->find[i].split, &world->ambient);
		}
		else if (split[0] && !ft_strcmp(split[0], "C"))
		{
			camera_data(data->find[i].split, &world->camera);
			printf("C id a detected\n");
		}
		else if (split[0] && !ft_strcmp(split[0], "L"))
		{
			light_data(data->find[i].split, &world->light);
			printf("L id a detected\n");
		}
		else if (split[0] && (!ft_strcmp(split[0], "pl") || !ft_strcmp(split[0], "sp") || !ft_strcmp(split[0], "cy")))
		{
			printf("obj detected\n");
		}
		else
			error_msg("Invalid input\n");
		i++;
	}
	// printf("-- %f\n", world->ambient.ratio);
	// printf("--> %.1f\n", world->light.brightness);
	return (world);
}

int main(int ac, char **av)
{
	t_data	data;

	(void)ac;
	(void)av;
	allocate_map("../artwork/test.rt", &data);
	split_data(&data);
	fill_data(&data);
	// display_map(&data.find[1].split[0]);
	// printf("* : %s\n", data.find[0].split[0]);
}