/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ppm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelayad <abelayad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 20:43:54 by ogorfti           #+#    #+#             */
/*   Updated: 2023/09/21 16:08:21 by abelayad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	ft_free_btex(t_btex *btex)
{
	int	i;

	if (!btex)
		return ;
	i = 0;
	while (i < btex->height)
		free(btex->pixels[i++]);
	free(btex->pixels);
	free(btex);
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
	ppm->leaks = ppm->read;
	free (joiner);
}

void	init_data(t_btex *ppm)
{
	char	**tmp;
	int		i;

	tmp = ft_split(ppm->read[1], ' ');
	ppm->width = ft_atoi(tmp[0]);
	ppm->height = ft_atoi(tmp[1]);
	ppm->pixels = ft_calloc(ppm->height, sizeof(t_color *));
	ppm->read += 3;
	i = 0;
	while (i < ppm->height)
	{
		ppm->pixels[i] = ft_calloc(ppm->width, sizeof(t_color));
		i++;
	}
	free_double(tmp);
}

void	ppm_data(t_btex *ppm)
{
	char	**tmp;
	char	**ptr;
	int		i;
	int		j;

	init_data(ppm);
	i = 0;
	while (i < ppm->height)
	{
		j = 0;
		tmp = ft_split(ppm->read[i], 32);
		ptr = tmp;
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
	free_double(ppm->leaks);
}
