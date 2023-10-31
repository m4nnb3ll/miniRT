/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelayad <abelayad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 16:12:33 by abelayad          #+#    #+#             */
/*   Updated: 2023/10/31 15:52:02 by abelayad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_matrix	ft_view_transform_inverse(t_tuple from, t_tuple to)
{
	t_tuple		forward;
	t_tuple		up;
	t_tuple		left;
	double		fdu;
	t_matrix	orientation;

	forward = ft_normalize(ft_sub_tuples(to, from));
	up = ft_vector(0, 1, 0);
	fdu = ft_dot(forward, up);
	if (fdu == 1 || fdu == -1)
		up = ft_vector(EPSILON * -fdu, 1, EPSILON * -fdu);
	left = ft_normalize(ft_cross(forward, up));
	up = ft_normalize(ft_cross(left, forward));
	orientation = (t_matrix){4,
	{
	{left.x, left.y, left.z, 0},
	{up.x, up.y, up.z, 0},
	{-forward.x, -forward.y, -forward.z, 0},
	{0, 0, 0, 1}
	}
	};
	return (ft_inverse(
			ft_multi_matrices(orientation,
				ft_translate(-from.x, -from.y, -from.z))));
}

t_camera	ft_camera(t_camera raw_camera)
{
	t_camera	c;
	double		half_view;
	double		aspect;

	c = raw_camera;
	half_view = tan(c.fov / 4) * 2;
	c.screen_w = SCREEN_WIDTH;
	c.screen_h = SCREEN_HEIGHT;
	aspect = (double)SCREEN_WIDTH / SCREEN_HEIGHT;
	if (aspect > 1)
	{
		c.half_c_w = half_view;
		c.half_c_h = c.half_c_w * (1 / aspect);
	}
	else
	{
		c.half_c_h = half_view;
		c.half_c_w = c.half_c_h * aspect;
	}
	c.psize = c.half_c_w * 2 / SCREEN_WIDTH;
	c.view_transform_inverse = ft_view_transform_inverse(c.from, c.to);
	return (c);
}

t_ray	ft_ray_for_pixel(int x, int y, int phase, t_camera c)
{
	double	world_x;
	double	world_y;
	t_ray	r;
	double	*hit_coords;

	hit_coords = (double[5 * 2]){.5, .5, .1, .1, .9, .1, .1, .9, .9, .9};
	world_x = c.half_c_w - (x + hit_coords[2 * phase]) * c.psize;
	world_y = c.half_c_h - (y + hit_coords[2 * phase + 1]) * c.psize;
	r = ft_ray(ft_point(0, 0, 0), ft_vector(world_x, world_y, -1));
	r = ft_transform_ray(c.view_transform_inverse, r);
	r.direction = ft_normalize(r.direction);
	return (r);
}

void	ft_render(t_png_img *img, t_world *w, int phase)
{
	t_color	color;
	int		i, j;
	
	i = phase * (img->height / w->cores_cnt);

	int end = (phase + 1) == w->cores_cnt ? img->height : (phase + 1) * (img->height / w->cores_cnt);
	
	while (i < /* img->height */ end)
	{
		j = 0;
		while (j < img->width)
		{
			color = g_black;
			for (int k = 0; k < 5; k++)
				color = ft_add_colors(
					color,
					ft_color_at(w, ft_ray_for_pixel(j, i, k, w->camera), REFLECT_DEPTH)
					);
				// I will see to make put pixel take a pointer to the img
			ft_png_put_pixel(*img, j, i, (t_color){color.r / 5, color.g / 5, color.b / 5});
			j++;
		}
		i++;
	}
	ft_free_objs_and_tex(w);;
}
