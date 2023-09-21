#include "minirt.h"

// int main()
// {
// 	t_obj	*middle;
// 	t_tuple	direction;
// 	t_ray	r;
// 	t_xnode	*xs;

// 	t_cone	*cone = ft_calloc(1, sizeof(t_cone));
// 	middle = ft_objnew(OT_CONE, cone);
// 	((t_cone*)(middle -> props)) -> height = 99999999;
// 	direction = ft_normalize(ft_vector(0, 0, 1));
// 	r = ft_ray(ft_point(0, 0, -5), direction);
// 	xs = ft_intersect_cone(middle, r);
// 	ft_print_xs(xs);

// 	direction = ft_normalize(ft_vector(1, 1, 1));
// 	r = ft_ray(ft_point(0, 0, -5), direction);
// 	xs = ft_intersect_cone(middle, r);
// 	ft_print_xs(xs);

// 	direction = ft_normalize(ft_vector(-.5, -1, 1));
// 	r = ft_ray(ft_point(1, 1, -5), direction);
// 	xs = ft_intersect_cone(middle, r);
// 	ft_print_xs(xs);

// 	direction = ft_normalize(ft_vector(0, 1, 1));
// 	r = ft_ray(ft_point(0, 0, -1), direction);
// 	xs = ft_intersect_cone(middle, r);
// 	ft_print_xs(xs);
	
// }

char *objs_strs[] = {
	"SPHERE",
	"PLANE",
	"CYLINDER",
	"CONE"
};

void	ft_print_material(t_material m)
{
	// ft_print_color(m.color);
	printf("%f %f %f %f\n", m.ambient, m.diffuse, m.specular, m.shininess);
}

void	ft_print_obj(t_obj *obj)
{
	// Type
	printf("the obj type is: %s\n", objs_strs[obj->type]);
	// Transform Inverse
	printf("The transform_inverse is:\n");
	// ft_print_matrix(obj->transform_inverse);
	// Material
	printf("The material is:\n");
	// ft_print_material(obj->material);
	printf("The props are: %p\n", obj->props);
}

// t_texture	ft_get_texture(int w, int h)
// {
// 	t_texture	texture;
// 	t_color		**pixels;

// 	pixels	= ft_calloc(h, sizeof(t_color*));
// 	for (int i = 0; i < h; i++)
// 		pixels[i] = ft_calloc(w, sizeof(t_color));
// 	for (int i = 0; i < h; i++)
// 	{
// 		for (int j = 0; j < w; j++)
// 		{
// 			if ((i + j)%2 == 0)
// 				pixels[i][j] = g_black;
// 			else
// 				pixels[i][j] = g_white;
// 		}
// 	}
// 	texture = (t_texture){w, h, pixels};
// 	return (texture);
// }

t_color	ft_uv_pattern_at(t_btex *texture, double u, double v) // u & v [0-1.0]
{
	if (!texture)
		return (g_black);
	int	x, y;

	x = (int)floor(u * (texture->width)) % texture->width;
	y = (int)floor(v * (texture->height)) % texture->height;
	// printf("the x and y are: %d %d\n", x, y);
	// printf("The x and y are: %d %d\n", x, y);
	// printf("The x is: %d and y is: %d\n", x, y);
	return	(texture->pixels[y][x]);
}

// t_tuple	ft_texture_normal_at(t_texture texture, double u, double v)
// {
// 	t_color	c;

// 	c = ft_uv_pattern_at(texture, u, v);
// 	return (ft_normalize(ft_vector(c.red, c.green, c.blue)));
// }

t_tuple	ft_planar_map(t_tuple op)// take only the x and y
{
	// printf("The x and y planar are: %d %d\n", (int)op.x % 1, (int)op.y);
	// printf("The op.x is: %d\n", (int)round(op.x));
	return ((t_tuple){fabs(fmod(op.x, 1)), fabs(fmod(op.y, 1)), 0, 0});
}

t_tuple	ft_spherical_map(t_tuple op)// take only the x and y
{
	double	theta, phi;
	t_tuple	vec;
	double	radius;
	double	u, v;

	theta = atan2(op.x, op.z);
	vec = ft_vector(op.x, op.y, op.z);
	radius = ft_mag(vec);
	phi = acos(op.y / radius);
	u = theta / (2 * PI);
	u = 1 - (u + .5);
	v = 1 - phi / PI;
	return ((t_tuple){u, v, 0, 0});
}

int main(/* int argc, char **argv */)
{
	t_world		w;

	world_data(&w, "test.rt");
	// w.objs[0].transform_inverse = ft_inverse(ft_rotate_y(PI/2));
	w.camera = ft_camera(w.camera);
	// t_window window = ft_img_ptr();
	t_window window;
	window = (t_window){0, 0};
	ft_render(window, &w, w.camera);
	// mlx_terminate(window.mlx);
}
// RENDERING GOES ABOVE ^^^

// TESTING GOES BELOW vvv
// int main()
// {
// 	t_texture	texture;
// 	t_color		color;

// 	texture = ft_get_texture(2, 2);
// 	color = ft_uv_pattern_at(texture, 0, 0);
// 	ft_print_color(color);
	
// 	color = ft_uv_pattern_at(texture, 0.5, 0);
// 	ft_print_color(color);
	
// 	color = ft_uv_pattern_at(texture, 0, 0.5);
// 	ft_print_color(color);
	
// 	color = ft_uv_pattern_at(texture, 0.5, 0.5);
// 	ft_print_color(color);
	
// 	color = ft_uv_pattern_at(texture, 1.0, 1.0);
// 	ft_print_color(color);
	
// }




// t_matrix

// int main()
// {
// 	t_tuple		a, b, v;
// 	double		s, c;
// 	t_matrix	vx;
// 	t_matrix	vx2;
// 	t_matrix	final;
 
// 	a = ft_normalize(ft_vector(-3.4, 6.1, 1.4));
// 	b = ft_normalize(ft_vector(7.1, 2.3, 4.1));
// 	v = ft_normalize(ft_cross(a, b));
// 	s = ft_mag(v);
// 	c = ft_dot(a, b);
// 	vx = (t_matrix){3, {
// 		{0, -v.z, v.y, 0},
// 		{v.z, 0, -v.x, 0},
// 		{-v.y, v.x, 0, 0},
// 		{0, 0, 0, 1}
// 	}};

// 	vx2 = ft_multi_matrices(vx, vx);
// 	// printf("The vx2 matrix is:\n");
// 	// ft_print_matrix(vx2);
// 	vx2 = ft_matrix_scl(vx2, (1-c)/pow(s, 2));
// 	final = ft_add_matrices(ft_add_matrices(vx, vx2), g_identity_matrix);
// 	// printf("The transformation matrix is:\n");
// 	// ft_print_matrix(final);
// 	printf("The transformed vector is:\n");
// 	ft_print_tuple(ft_transform_tuple(final, a));
// 	printf("b normalized is:\n");
// 	ft_print_tuple(b);

// 	/* ---------------------------------------------------- */

// 	t_tuple     v1, v2;
//     t_matrix    m;

//     v1 = ft_normalize(ft_vector(.341, 1.142, .69420));
//     v2 = ft_normalize(ft_vector(54.4150, 3.1574, 25.124));
//     m = ft_get_rotation_matrix(v1, v2);
// 	printf("The matrix is:\n");
// 	ft_print_matrix(m);
//     printf("The transformed v1 is:\n");
//     ft_print_tuple(ft_transform_tuple(m, v1));
//     printf("V2 is:\n");
//     ft_print_tuple(v2);
// }


// void	ft_print_ambient(t_ambient a)
// {
// 	printf("The ambient is:\n");
// 	printf("ratio: %f\n", a.ratio);
// 	ft_print_color(a.color);
// }

// void	ft_print_camera(t_camera cam)
// {
// 	printf("The camera is:\n");
// 	ft_print_tuple(cam.pt);
// 	ft_print_tuple(cam.forward_v);
// 	printf("The fov is: %f\n", cam.fov);
// }