/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelayad <abelayad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 16:09:43 by abelayad          #+#    #+#             */
/*   Updated: 2023/09/21 16:10:57 by abelayad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// u & v [0-1.0]
t_color	ft_uv_pattern_at(t_btex *texture, double u, double v)
{
	int	x;
	int	y;

	if (!texture)
		return (g_black);
	x = (int)floor(u * (texture->width)) % texture->width;
	y = (int)floor(v * (texture->height)) % texture->height;
	return (texture->pixels[y][x]);
}

// take only the x and y
t_tuple	ft_planar_map(t_tuple op)
{
	return ((t_tuple){fabs(fmod(op.x, 1)), fabs(fmod(op.y, 1)), 0, 0});
}

int	main(int argc, char **argv)
{
	t_world		w;
	t_window	window;

	if (argc != 2)
		return (printf("Please provide a scene file!\n"), -42);
	world_data(&w, argv[1]);
	w.camera = ft_camera(w.camera);
	window = ft_img_ptr();
	ft_render(window, &w, w.camera);
}
