/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocate_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogorfti <ogorfti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 17:22:23 by ogorfti           #+#    #+#             */
/*   Updated: 2023/09/15 19:47:24 by ogorfti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

void	allocate_map(char *file, t_data *data)
{
	char	*joiner;
	char	*leak;
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
		leak = joiner;
		joiner = ft_strjoin(leak, line);
		free (leak);
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
	data->find = ft_calloc(sizeof(t_find), (data->mapsize + 1));
	if (!data->find)
		exit (1);
	while (data->map[i])
	{
		data->find[i].split = split_string(data->map[i]);
		i++;
	}
}

int	calculate_objs(t_data *data)
{
	char **split;
	int count;
	int i;

	i = 0;
	count = 0;
	while (data->find[i].split)
	{
		split = &data->find[i].split[0];
		if (split[0] && (!ft_strcmp(split[0], "pl") || !ft_strcmp(split[0], "sp") || !ft_strcmp(split[0], "cy")))
			count++;
		i++;
	}
	return (count);
}