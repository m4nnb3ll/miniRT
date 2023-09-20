/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ppm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelayad <abelayad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 20:43:54 by ogorfti           #+#    #+#             */
/*   Updated: 2023/09/20 13:41:40 by abelayad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	free_color(t_color **color)
{
	int i;

	i = 0;
	while (color[i])
	{
		free (color[i]);
		color[i] = 0;
		i++;
	}
	free(color);
}

void	readppm(char *file, t_btex *ppm)
{
	char	*joiner;
	char	*leak;
	char	*line;
	int		fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		error_msg("Error opening file\n");
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

void	ppm_data(t_btex *ppm)
{
	char	**tmp;
	char 	**tmp1;
	int		i = 0;
	int		j = 0;

	tmp1 = ppm->read;
	tmp = ft_split(ppm->read[1], 32);
	ppm->width = ft_atoi(tmp[0]);
	ppm->height = ft_atoi(tmp[1]);
	ppm->pixels = ft_calloc(ppm->height, sizeof(t_color *));
	ppm->read += 3;
	while (i < ppm->height)
	{
		ppm->pixels[i] = ft_calloc(ppm->width, sizeof(t_color));
		i++;
	}
	i = 0;
	free_double(tmp);
	tmp = NULL;
	while (i < ppm->height)
	{
		j = 0;
		tmp = ft_split(ppm->read[i], 32);
		char **ptr = tmp;
		while (j < ppm->width)
		{
			ppm->pixels[i][j].r = translatecolor(my_strtod(tmp[0]));
			ppm->pixels[i][j].g = translatecolor(my_strtod(tmp[1]));
			ppm->pixels[i][j].b = translatecolor(my_strtod(tmp[2]));
			tmp += 3;
			j++;
		}
		free_double(ptr);
		i++;
	}
	free_double(tmp1);
}



// this how to use it just call
// 	t_btex	ppm;
// 	readppm("file.ppm", &ppm);
// 	ppm_data(&ppm);
// call free_color(ppm->color); after finishing its use