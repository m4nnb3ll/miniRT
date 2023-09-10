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
		up = ft_vector(EPSILON * -fdu, 1, EPSILON * -fdu);// change this to just fdu later
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

t_camera	ft_camera(int screen_w, int screen_h, double fov)
{
	t_camera	camera;
	double		half_view;
	double		aspect;

	half_view = tan(fov / 4) * 2;
	camera.screen_w = screen_w;
	camera.screen_h = screen_h;
	aspect = (double)screen_w / screen_h;
	if (aspect > 1)
	{
		camera.half_c_w = half_view;
		camera.half_c_h = camera.half_c_w * (1 / aspect);
	}
	else
	{
		camera.half_c_h = half_view;
		camera.half_c_w = camera.half_c_h * aspect;
	}
	camera.psize = camera.half_c_w * 2 / screen_w;
	camera.view_transform_inverse = g_identity_matrix;
	return (camera);
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

t_canvas	ft_render(t_world w, t_camera c)
{
	t_ray			r;
	t_canvas	canvas;

	for (int i = 0; i < c.screen_h; i++)
	{
		for (int j = 0; j < c.screen_w; j++)
		{
			r = ft_ray_for_pixel(j, i, c);
			canvas.pixel_grid[i][j] = ft_color_at(w, r);
		}
	}	
	return (canvas);
}
