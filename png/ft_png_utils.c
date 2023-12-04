/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_png_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelayad <abelayad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 11:38:19 by abelayad          #+#    #+#             */
/*   Updated: 2023/12/04 12:40:34 by abelayad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// Changes the color from [0, 1] range to [0, 255] range
void	ft_png_put_pixel(t_png_img *img, int x, int y, t_color color)
{
	if (x >= img->width || y >= img->height)
		return ;
	img->row_pointers[y][x * 4 + 0] = ft_255channel(color.r);
	img->row_pointers[y][x * 4 + 1] = ft_255channel(color.g);
	img->row_pointers[y][x * 4 + 2] = ft_255channel(color.b);
	img->row_pointers[y][x * 4 + 3] = 0xff;
}

t_png_img	ft_allocate_png_img(int width, int height)
{
	t_png_img	img;

	img.row_pointers = (png_bytep *)calloc(height, sizeof(png_bytep));
	if (!img.row_pointers)
		return ((t_png_img){0, 0, NULL});
	for (int i = 0; i < height; i++)
	{
		img.row_pointers[i] = (png_byte *)calloc(width * 4, sizeof(png_byte));
		if (!img.row_pointers[i])
			return ((t_png_img){0, 0, NULL});
	}
	return ((t_png_img){width, height, img.row_pointers});
}
