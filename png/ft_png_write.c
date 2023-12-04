/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_png_write.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelayad <abelayad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 11:34:44 by abelayad          #+#    #+#             */
/*   Updated: 2023/12/04 12:40:19 by abelayad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	ft_png_write_file_check(
	char *filename, FILE **fp, png_structp *png, png_infop *info)
{
	*fp = fopen(filename, "wb");
	if (!*fp)
		return (dprintf(2, "Error opening the file for writing\n"), false);
	*png = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if (!*png)
		return (fclose(*fp),
			dprintf(2, "Error creating PNG write structure\n"), false);
	*info = png_create_info_struct(*png);
	if (!*info)
		return (fclose(*fp), png_destroy_write_struct(png, NULL),
			dprintf(2, "Error creating PNG info structure\n"), false);
	if (setjmp(png_jmpbuf(*png)))
		return (fclose(*fp), png_destroy_write_struct(png, info),
			dprintf(2, "Error writing the PNG file\n"), false);
	return (true);
}

bool	ft_write_png_file(char *filename, t_png_img png_img)
{
	FILE		*fp;
	png_structp	png;
	png_infop	info;

	if (!ft_png_write_file_check(filename, &fp, &png, &info))
		return (false);
	png_init_io(png, fp);
	png_set_IHDR(
		png,
		info,
		png_img.width, png_img.height,
		8,
		PNG_COLOR_TYPE_RGBA,
		PNG_INTERLACE_NONE,
		PNG_COMPRESSION_TYPE_DEFAULT,
		PNG_FILTER_TYPE_DEFAULT
		);
	png_write_info(png, info);
	png_write_image(png, png_img.row_pointers);
	png_write_end(png, NULL);
	for (int y = 0; y < png_img.height; y++)
		free(png_img.row_pointers[y]);
	free(png_img.row_pointers);
	return (fclose(fp), png_destroy_write_struct(&png, &info), true);
}
