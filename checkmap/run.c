/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogorfti <ogorfti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 17:34:38 by ogorfti           #+#    #+#             */
/*   Updated: 2023/09/12 20:32:54 by ogorfti          ###   ########.fr       */
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

void	error_msg(char *str)
{
	ft_putstr_fd(str, 1);
	exit (1);
}

void	allocate_map(char *file, t_minirt *minirt)
{
	char	*joiner;
	char	*line;
	int		fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		error_msg("Error: File open failed.\n");
	joiner = ft_calloc(1, 1);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		joiner = ft_strjoin(joiner, line);
		free (line);
	}
	minirt->map = ft_split(joiner, '\n');
	free (joiner);
	display_map(minirt->map);
}

int main(int ac, char **av)
{
	t_minirt minirt;
	(void)ac;
	(void)av;
	allocate_map("../artwork/test.rt", &minirt);
}