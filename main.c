/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelayad <abelayad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 16:09:43 by abelayad          #+#    #+#             */
/*   Updated: 2023/09/25 12:27:46 by abelayad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// u & v [0-1.0]
t_color	ft_uv_pattern_at(t_btex texture, double u, double v)
{
	int	x;
	int	y;

	if (!texture.pixels)
		return (g_black);
	x = (int)floor(u * (texture.width)) % texture.width;
	y = (int)floor(v * (texture.height)) % texture.height;
	return (texture.pixels[y][x]);
}

// take only the x and y
t_tuple	ft_planar_map(t_tuple op)
{
	return ((t_tuple){fabs(fmod(op.x, 1)), fabs(fmod(op.y, 1)), 0, 0});
}

int	main(int argc, char **argv)
{
	t_world		w;
	// t_window	window;
	t_png_img	img;

	if (argc != 2)
		return (printf("Please provide a scene file!\n"), -42);
	world_data(&w, argv[1]);
	w.camera = ft_camera(w.camera);
	// window = ft_img_ptr();
	img = ft_allocate_png_img(SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!img.row_pointers)
		return (printf("Error allocating the image\n"), -42);
	ft_render(img, &w, w.camera);
}
