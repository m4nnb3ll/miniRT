/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_png.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelayad <abelayad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 11:36:08 by abelayad          #+#    #+#             */
/*   Updated: 2023/10/27 20:34:01 by abelayad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PNG_H
# define FT_PNG_H

# include "minirt_types.h"

bool		ft_png_read_file_check(
				char *filename, FILE **fp, png_structp *png, png_infop *info);
void		ft_png_modify_read_info(
				png_structp *png, png_infop *info,
				png_byte bit_depth, png_byte color_type);
t_png_img	ft_read_png_file(char *filename);
bool		ft_png_write_file_check(
				char *filename, FILE **fp, png_structp *png, png_infop *info);
bool		ft_write_png_file(char *filename, t_png_img png_img);
void		ft_png_put_pixel(t_png_img img, int x, int y, t_color color);
t_png_img	ft_allocate_png_img(int width, int height);
t_tex		ft_png_img_to_tex(t_png_img img);
void		ft_free_tex(t_tex tex);

#endif