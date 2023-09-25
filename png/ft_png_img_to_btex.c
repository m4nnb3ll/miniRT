/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_png_img_to_btex.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelayad <abelayad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 12:08:07 by abelayad          #+#    #+#             */
/*   Updated: 2023/09/25 12:49:30 by abelayad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	ft_free_btex(t_btex btex)
{
	int	i;

	if (!btex.pixels)
		return ;
	i = 0;
	while (i < btex.height)
		free(btex.pixels[i++]);
	free(btex.pixels);
}

t_btex	ft_png_img_to_btex(t_png_img img)
{
	t_btex	btex;

	btex.pixels = (t_color **)ft_calloc(img.height, sizeof(t_color *));
	if (!btex.pixels)
		return ((t_btex){0, 0, NULL});
	for (int i = 0; i < img.height; i++)
	{
		btex.pixels[i] = (t_color *)ft_calloc(img.width, sizeof(t_color));
		if (!btex.pixels[i])
			return ((t_btex){0, 0, NULL});
	}
	for (int i = 0; i < img.height; i++)
	{
		for (int j = 0; j < img.width; j++)
		{
			btex.pixels[i][j].r = img.row_pointers[i][j * 4 + 0];
			btex.pixels[i][j].g = img.row_pointers[i][j * 4 + 1];
			btex.pixels[i][j].b = img.row_pointers[i][j * 4 + 2];
		}
	}
	return ((t_btex){img.width, img.height, btex.pixels});
}
