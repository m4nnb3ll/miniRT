/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogorfti <ogorfti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 17:02:55 by ogorfti           #+#    #+#             */
/*   Updated: 2023/09/17 13:56:44 by ogorfti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minirt.h"

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

//converts a color value from the range of 0 to 255 to a normalized range of 0.0 to 1.0
double translatecolor(double color)
{
	double tr;

	tr = 0.0;
	if (color < 0 || color > 255)
		error_msg("Error: Invalid color value\n");
	else
		tr = color / 255.0;
	return (tr);
}

//verifies if tuple components are within the range [-1, 1]
int	check_range(t_tuple tuple)
{
	if (tuple.x < -1 || tuple.x > 1 || tuple.y < -1 || tuple.y > 1 || tuple.z < -1 || tuple.z > 1)
		return (1);
	return (0);
}

void	free_double(char **ptr)
{
	int	i;

	i = 0;
	if (ptr) 
	{
		while (ptr[i])
		{
			free(ptr[i]);
			ptr[i] = NULL;
			i++;
		}
		free(ptr);
	}
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

int	check_name(char *str)
{
	if (ft_strlen(str) <= 3 || ft_strcmp(str + ft_strlen(str) - 3, ".rt"))
		return (1);
	return (0);
}
