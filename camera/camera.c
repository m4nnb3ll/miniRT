/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelayad <abelayad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 16:12:33 by abelayad          #+#    #+#             */
/*   Updated: 2023/12/02 16:40:43 by abelayad         ###   ########.fr       */
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
	return (ft_inverse(ft_multi_matrices(
				orientation, ft_translate(-from.x, -from.y, -from.z))));
}

t_camera	ft_camera(t_camera c)
{
	double		half_view;
	double		aspect;

	c.fov /= 180;
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

	hit_coords = (double [5 * 2]){.5, .5, .1, .1, .9, .1, .1, .9, .9, .9};
	world_x = c.half_c_w - (x + hit_coords[2 * phase]) * c.psize;
	world_y = c.half_c_h - (y + hit_coords[2 * phase + 1]) * c.psize;
	r = ft_ray(ft_point(0, 0, 0), ft_vector(world_x, world_y, -1));
	r = ft_transform_ray(c.view_transform_inverse, r);
	r.direction = ft_normalize(r.direction);
	return (r);
}

t_color	ft_anti_aliased_color(t_world *w, int j, int i)
{
	t_color	color;
	t_ray	r;
	int		k;

	color = g_black;
	k = 0;
	while (k < 5)
	{
		r = ft_ray_for_pixel(j, i, k, w->camera);
		color = ft_add_colors(color, ft_color_at(w, r, REFLECT_DEPTH));
		k++;
	}
	return ((t_color){color.r / 5, color.g / 5, color.b / 5});
}

void	ft_render(t_png_img *img, t_world *w, int thread_i)
{
	int		i;
	int		j;
	int		end;
	int		chunk_size;

	chunk_size = img->height / w->cores_cnt;
	i = thread_i * (chunk_size);
	if ((thread_i + 1) == w->cores_cnt)
		end = img->height;
	else
		end = (thread_i + 1) * (chunk_size);
	while (i < end)
	{
		j = 0;
		while (j < img->width)
		{
			ft_png_put_pixel(img, j, i, ft_anti_aliased_color(w, j, i));
			j++;
		}
		i++;
	}
}
