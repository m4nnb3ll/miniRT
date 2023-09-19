/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ppm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogorfti <ogorfti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 13:18:06 by ogorfti           #+#    #+#             */
/*   Updated: 2023/09/19 16:20:28 by ogorfti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	readppm(char *file, t_ppm *ppm)
{
	char	*joiner;
	char	*leak;
	char	*line;
	int		fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		error_msg("Error opening file\n");
		exit (13);
	}
	joiner = ft_calloc(1, 1);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		leak = joiner;
		joiner = ft_strjoin(leak, line);
		free (leak);
		free (line);
	}
	ppm->read = ft_split(joiner, '\n');
	free (joiner);
}

void	ppm_data(t_ppm *ppm)
{
	char	**tmp;
	int		i = 0;
	int		j = 0;

	printf("test0\n");
	tmp = ft_split(ppm->read[1], 32);
	ppm->width = ft_atoi(tmp[0]);
	ppm->height = ft_atoi(tmp[1]);
	ppm->color = ft_calloc(ppm->height, sizeof(t_color *));
	ppm->read += 3;
	while (i < ppm->height)
	{
		ppm->color[i] = ft_calloc(ppm->width, sizeof(t_color));
		i++;
	}
	i = 0;
	// free_double(tmp);
	while (i < ppm->height)
	{
		j = 0;
		tmp = ft_split(ppm->read[i], 32);
		while (j < ppm->width)
		{
			ppm->color[i][j].r = translatecolor(my_strtod(tmp[0]));
			ppm->color[i][j].g = translatecolor(my_strtod(tmp[1]));
			ppm->color[i][j].b = translatecolor(my_strtod(tmp[2]));
			tmp += 3;
			j++;
		}
		// free_double(tmp);
		i++;
	}
}


// this how to use it just call
// 	t_ppm	ppm;
// 	readppm("file.ppm", &ppm);
// 	ppm_data(&ppm);
