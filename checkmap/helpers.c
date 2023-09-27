/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelayad <abelayad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 17:02:55 by ogorfti           #+#    #+#             */
/*   Updated: 2023/09/26 20:32:13 by abelayad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	s1_len;
	size_t	s2_len;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	if (s1_len > s2_len)
		return (ft_strncmp(s1, s2, s1_len));
	else
		return (ft_strncmp(s1, s2, s2_len));
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
