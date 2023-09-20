/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogorfti <ogorfti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 17:02:55 by ogorfti           #+#    #+#             */
/*   Updated: 2023/09/20 20:31:21 by ogorfti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

void	error_msg(char *str)
{
	ft_putstr_fd(str, 1);
	exit (1);
}

int	nbr_info(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

//converts a color to a normalized range [0.0, 1.0]
double	translatecolor(double color)
{
	double	tr;

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
	if (tuple.x < -1 || tuple.x > 1 || tuple.y < -1
		|| tuple.y > 1 || tuple.z < -1 || tuple.z > 1)
		return (1);
	return (0);
}
