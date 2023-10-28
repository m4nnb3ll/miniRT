/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_png_img_to_tex.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelayad <abelayad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 12:08:07 by abelayad          #+#    #+#             */
/*   Updated: 2023/09/25 12:49:30 by abelayad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	ft_free_tex(t_tex tex)
{
	int	i;

	if (!tex.pixels)
		return ;
	i = 0;
	while (i < tex.height)
		free(tex.pixels[i++]);
	free(tex.pixels);
}

t_tex	ft_png_img_to_tex(t_png_img img)
{
	t_tex	tex;

	tex.pixels = (t_color **)ft_calloc(img.height, sizeof(t_color *));
	if (!tex.pixels)
		return ((t_tex){0, 0, NULL});
	for (int i = 0; i < img.height; i++)
	{
		tex.pixels[i] = (t_color *)ft_calloc(img.width, sizeof(t_color));
		if (!tex.pixels[i])
			return ((t_tex){0, 0, NULL});
	}
	for (int i = 0; i < img.height; i++)
	{
		for (int j = 0; j < img.width; j++)
		{
			tex.pixels[i][j].r = img.row_pointers[i][j * 4 + 0] / 255.0;
			tex.pixels[i][j].g = img.row_pointers[i][j * 4 + 1] / 255.0;
			tex.pixels[i][j].b = img.row_pointers[i][j * 4 + 2] / 255.0;
		}
	}
	return ((t_tex){img.width, img.height, tex.pixels});
}
