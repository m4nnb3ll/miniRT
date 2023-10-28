/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_png_read.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelayad <abelayad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 11:33:32 by abelayad          #+#    #+#             */
/*   Updated: 2023/10/28 12:57:03 by abelayad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	ft_png_read_file_check(
			char *filename, FILE **fp, png_structp *png, png_infop *info)
{
	*fp = fopen(filename, "rb");
	if (!*fp)
		return (dprintf(2, "Error opening the file for reading\n"), false);
	*png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if (!*png)
		return (fclose(*fp),
			dprintf(2, "Error creating PNG read structure\n"), false);
	*info = png_create_info_struct(*png);
	if (!*info)
		return (fclose(*fp), png_destroy_read_struct(png, NULL, NULL),
			dprintf(2, "Error creating PNG info structure\n"), false);
	if (setjmp(png_jmpbuf(*png)))
		return (fclose(*fp), png_destroy_read_struct(png, info, NULL),
			dprintf(2, "Error reading the PNG file\n"), false);
	return (true);
}

void	ft_png_modify_read_info(
	png_structp *png, png_infop *info, png_byte bit_depth, png_byte color_type)
{
	if (bit_depth == 16)
		png_set_strip_16(*png);
	if (color_type == PNG_COLOR_TYPE_PALETTE)
		png_set_palette_to_rgb(*png);
	if (color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8)
		png_set_expand_gray_1_2_4_to_8(*png);
	if (png_get_valid(*png, *info, PNG_INFO_tRNS))
		png_set_tRNS_to_alpha(*png);
	if (color_type == PNG_COLOR_TYPE_RGB
		|| color_type == PNG_COLOR_TYPE_GRAY
		|| color_type == PNG_COLOR_TYPE_PALETTE)
		png_set_filler(*png, 0xFF, PNG_FILLER_AFTER);
	if (color_type == PNG_COLOR_TYPE_GRAY
		|| color_type == PNG_COLOR_TYPE_GRAY_ALPHA)
		png_set_gray_to_rgb(*png);
	png_read_update_info(*png, *info);
}

t_png_img	ft_read_png_file(char *filename)
{
	FILE		*fp;
	png_structp	png;
	png_infop	info;
	t_png_img	img;

	img = (t_png_img){0, 0, NULL};
	if (!ft_png_read_file_check(filename, &fp, &png, &info))
		exit(53);
		// return (img); // i ll see why i was doing this
	png_init_io(png, fp);
	png_read_info(png, info);
	img.width = png_get_image_width(png, info);
	img.height = png_get_image_height(png, info);
	ft_png_modify_read_info(&png, &info,
		png_get_bit_depth(png, info), png_get_color_type(png, info));
	img.row_pointers = (png_bytep *)malloc(sizeof(png_bytep) * img.height);
	for (int y = 0; y < img.height; y++)
		img.row_pointers[y] = (png_byte *)malloc(png_get_rowbytes(png, info));
	png_read_image(png, img.row_pointers);
	fclose(fp);
	png_destroy_read_struct(&png, &info, NULL);
	printf("Finished reading the png file\n");
	return (img);
}
