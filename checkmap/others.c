/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   others.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogorfti <ogorfti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 20:29:03 by ogorfti           #+#    #+#             */
/*   Updated: 2023/09/20 20:41:13 by ogorfti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
	int	i;

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

void	init_count(t_count *count, int *i)
{
	*i = 0;
	count->A = 0;
	count->C = 0;
	count->L = 0;
	count->l = 0;
}

void	check_count(t_data *data)
{
	t_count	count;
	char	**split;
	int		i;

	init_count(&count, &i);
	while (data->find[i].split)
	{
		split = &data->find[i].split[0];
		if (split[0] && !ft_strcmp(split[0], "A"))
			count.A++;
		else if (split[0] && !ft_strcmp(split[0], "C"))
			count.C++;
		else if (split[0] && !ft_strcmp(split[0], "L"))
			count.L++;
		else if (split[0] && !ft_strcmp(split[0], "l"))
			count.l++;
		else if (split[0] && ft_strcmp(split[0], "pl")
			&& ft_strcmp(split[0], "sp") && ft_strcmp(split[0], "cy")
			&& ft_strcmp(split[0], "cn"))
			error_msg("Invalid input\n");
		i++;
	}
	if (count.A != 1 || count.C != 1 || count.L != 1 || count.l > 1)
		error_msg("Invalid input\n");
}
