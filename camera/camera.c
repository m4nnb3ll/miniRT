/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelayad <abelayad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 16:12:33 by abelayad          #+#    #+#             */
/*   Updated: 2023/10/29 20:04:52 by abelayad         ###   ########.fr       */
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

t_ray	ft_ray_for_pixel(int x, int y, t_camera c,/* test*/ t_ray *ray_arr)
{
	double	world_x;
	double	world_y;
	t_ray	r;

	// ray 1
	world_x = c.half_c_w - (x + .5) * c.psize;
	world_y = c.half_c_h - (y + .5) * c.psize;
	r = ft_ray(ft_point(0, 0, 0), ft_vector(world_x, world_y, -1));
	r = ft_transform_ray(c.view_transform_inverse, r);
	r.direction = ft_normalize(r.direction);
	ray_arr[0] = r;
	// printf("The first ray is:\n");
	// ft_print_ray(ray_arr[0]);
	// ft_print_ray(r);
	// ray 2
	world_x = c.half_c_w - (x + .1) * c.psize;
	world_y = c.half_c_h - (y + .1) * c.psize;
	r = ft_ray(ft_point(0, 0, 0), ft_vector(world_x, world_y, -1));
	r = ft_transform_ray(c.view_transform_inverse, r);
	r.direction = ft_normalize(r.direction);
	ray_arr[1] = r;
	// // ray 3
	world_x = c.half_c_w - (x + .9) * c.psize;
	world_y = c.half_c_h - (y + .9) * c.psize;
	r = ft_ray(ft_point(0, 0, 0), ft_vector(world_x, world_y, -1));
	r = ft_transform_ray(c.view_transform_inverse, r);
	r.direction = ft_normalize(r.direction);
	ray_arr[2] = r;
	// ray 4
	world_x = c.half_c_w - (x + .1) * c.psize;
	world_y = c.half_c_h - (y + .9) * c.psize;
	r = ft_ray(ft_point(0, 0, 0), ft_vector(world_x, world_y, -1));
	r = ft_transform_ray(c.view_transform_inverse, r);
	r.direction = ft_normalize(r.direction);
	ray_arr[3] = r;
	// ray 5
	world_x = c.half_c_w - (x + .9) * c.psize;
	world_y = c.half_c_h - (y + .1) * c.psize;
	r = ft_ray(ft_point(0, 0, 0), ft_vector(world_x, world_y, -1));
	r = ft_transform_ray(c.view_transform_inverse, r);
	r.direction = ft_normalize(r.direction);
	ray_arr[4] = r;

	return (r);
}

t_color	ft_color_div(t_color c, int n)
{
	return ((t_color){c.r / n, c.g / n, c.b / n});
}

void	ft_render(t_png_img img, t_world w, t_camera c /* for test ->*/, int phase)
{
	t_color	color/* , tmp_color */;
	t_color	color_arr[5];
	// ft_bzero(&color_arr[0], sizeof(t_color) * 5);
	// t_ray	r;
	int		i;
	int		j;
	// test below
	// t_ray	ray_arr[5];
	t_ray	*ray_arr;
	ray_arr = ft_calloc(5, sizeof(t_ray));
	// ft_bzero(&ray_arr, sizeof(t_ray) * 5);

	// for initial test phase is going to be boolean
	i = phase * (img.height / 4);
	int end = (phase + 1) * (img.height / 4);
	while (i < /* img.height */end)
	{
		// printf("from thread %d\n", phase);
		j = 0;
		while (j < img.width)
		{
			/* r =  */ft_ray_for_pixel(j, i, c,/*test ->*/ ray_arr);
			// r = ray_arr[0];
			// printf("the ray from the loop is:\n");
			// ft_print_ray(ray_arr[0]);
			color_arr[0] = ft_color_at(&w, ray_arr[0], REFLECT_DEPTH);
			color_arr[1] = ft_color_at(&w, ray_arr[1], REFLECT_DEPTH);
			color_arr[2] = ft_color_at(&w, ray_arr[1], REFLECT_DEPTH);
			color_arr[3] = ft_color_at(&w, ray_arr[1], REFLECT_DEPTH);
			color_arr[4] = ft_color_at(&w, ray_arr[1], REFLECT_DEPTH);
			color = ft_add_colors(color_arr[0], color_arr[1]);
			color_arr[0] = ft_add_colors(color, color_arr[2]);
			color = ft_add_colors(color_arr[0], color_arr[3]);
			color_arr[0] = ft_add_colors(color, color_arr[4]);
			color = ft_color_div(color_arr[0], 5);
			// color = ft_color_at(w, ray_arr[0], REFLECT_DEPTH);
			ft_png_put_pixel(img, j, i, color);
			j++;
		}
		i++;
	}
	// ft_free_objs_and_tex(w);
	ft_write_png_file("scene.png", img);
}
