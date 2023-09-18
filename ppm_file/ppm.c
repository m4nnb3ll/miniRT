/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ppm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogorfti <ogorfti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 13:18:06 by ogorfti           #+#    #+#             */
/*   Updated: 2023/09/19 00:23:13 by ogorfti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../libft/include/libft.h"
// #include <stdio.h>
// #include <fcntl.h>
// #include <unistd.h>
// #include <stdlib.h>

#include "minirt.h"

// void	display_map(char **map)
// {
// 	int i;

// 	i = 0;
// 	while (map[i])
// 	{
// 		printf("%s\n", map[i]);
// 		i++;
// 	}
// }

// typedef struct s_color
// {
// 	double r;
// 	double g;
// 	double b;
// } t_color;

// typedef struct s_ppm
// {
// 	t_color	**color;
// 	char	**read;
// 	int		width;
// 	int		height;
// } t_ppm;

/*-----------*/

void	readppm(char *file, t_ppm *ppm)
{
	char	*joiner;
	char	*leak;
	char	*line;
	int		fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		exit (13);
	}
		// error_msg("Error opening file\n");
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
	// close(fd);
	free (joiner);
}

void	put_color(t_color *color, char **tmp)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	color->r = ft_atoi(tmp[0]);
	color->g = ft_atoi(tmp[1]);
	color->b = ft_atoi(tmp[2]);
	// color->r = translatecolor(my_strtod(tmp[0]));
	// color->g = translatecolor(my_strtod(tmp[1]));
	// color->b = translatecolor(my_strtod(tmp[2]));
}

void	ppm_data(t_ppm *ppm)
{
	char	**tmp;
	int		i = 0;
	int		j = 0;

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
			put_color(&ppm->color[i][j], tmp);
			tmp += 3;
			j++;
		}
		// free_double(tmp);
		i++;
	}
	// printf("w : %f\n", ppm->color[1][2].r);
	// printf("w : %f\n", ppm->color[1][2].g);
	// printf("w : %f\n", ppm->color[1][2].b);
}

// int main()
// {
// 	t_ppm	ppm;

// 	readppm("file.ppm", &ppm);
// 	ppm_data(&ppm);
// }
