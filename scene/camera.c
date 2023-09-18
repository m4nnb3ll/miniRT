#include "minirt.h"

t_matrix	ft_view_transform_inverse(t_tuple from, t_tuple forward)
{
	// the forward SHOULD BE NORMALIZED!!!
	t_tuple		up;
	t_tuple		left;
	double		fdu;
	t_matrix	orientation;

	up = ft_vector(0, 1, 0);
	fdu = ft_dot(forward, up);
	if (fdu == 1 || fdu == -1)
		up = ft_vector(EPSILON * -fdu, 1, EPSILON * -fdu);
	left = ft_normalize(ft_cross(forward, up));
	up = ft_normalize(ft_cross(left, forward));
	orientation = (t_matrix){4,
		{
			{ left.x, left.y, left.z, 0 },
			{ up.x, up.y, up.z, 0 },
			{ -forward.x, -forward.y, -forward.z, 0 },
			{ 0, 0, 0, 1 }
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
	c.view_transform_inverse = ft_view_transform_inverse(c.pt, c.forward_v);
	// printf("The transform inverse is\n");
	// ft_print_matrix(c.view_transform_inverse);
	return (c);
}

t_ray	ft_ray_for_pixel(int x, int y, t_camera c)
{
	double	world_x, world_y;
	t_ray		r;

	world_x = c.half_c_w - (x + .5) * c.psize;
	world_y = c.half_c_h - (y + .5) * c.psize;
	r = ft_ray(ft_point(0, 0, 0), ft_vector(world_x, world_y, -1));
	r = ft_transform_ray(c.view_transform_inverse, r);
	// printf("the view_transform\n");
	// ft_print_matrix(c.view_transform_inverse);
	r.direction = ft_normalize(r.direction);
	return (r);
}

uint32_t	ft_merge_colors(int r, int g, int b, int a)
{
	if (ENDIANESS == 0)
		return (a << 24 | b << 16 | g << 8 | r);
	return (r << 24 | g << 16 | b << 8 | a);
}

void	ft_render(t_window window, t_world *w, t_camera c)
{
	t_color	color;
	t_ray			r;
	// t_canvas	canvas;

	for (uint32_t i = 0; i < window.img->height; i++)
	{
		for (uint32_t j = 0; j < window.img->width; j++)
		{
			r = ft_ray_for_pixel(j, i, c);
			color = ft_color_at(w, r);
			mlx_put_pixel(window.img, j, i, ft_merge_colors(
				ft_255channel(color.r),
				ft_255channel(color.g),
				ft_255channel(color.b), 0xFF
			));
			// canvas.pixel_grid[i][j] = ;
		}
	}
	mlx_image_to_window(window.mlx, window.img, 0, 0);
	mlx_loop(window.mlx);
}
