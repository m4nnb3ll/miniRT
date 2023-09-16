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

int main()
{
	t_obj	*floor, *wall;

	// FLOOR
	t_plane	*pl = ft_calloc(1, sizeof(t_plane));
	floor = ft_objnew(OT_PLANE, pl);
	((t_plane*)(floor -> props)) -> normal = ft_vector(0, 1, 0);
	((t_plane*)(floor -> props)) -> pt = ft_point(0, 0, 0);
	floor -> material.color = ft_color(1, 0, 0);
	// floor -> transform_inverse = ft_inverse(ft_translate(0, -1, 0));
	// floor->material.specular = 0;

	// wall
	pl = ft_calloc(1, sizeof(t_plane));
	wall = ft_objnew(OT_PLANE, pl);
	((t_plane*)(wall -> props)) -> normal = ft_normalize(ft_vector(0, 1, 1));
	((t_plane*)(wall -> props)) -> pt = ft_point(0, 0, 0);
	wall -> material.color = ft_color(1, 1, 0);
	t_matrix	rot = ft_get_rotation_matrix(ft_vector(0, 1, 0), ((t_plane*)(wall -> props)) -> normal);
	wall -> transform_inverse = ft_inverse(ft_multi_matrices(/* ft_translate(0, -1, 0) */g_identity_matrix, rot));
	// wall->material.specular = 0;

	// OBJS
	t_obj	*middle;

	t_cone	*cone = ft_calloc(1, sizeof(t_cone));
	middle = ft_objnew(OT_CONE, cone);
	((t_cone*)(middle -> props)) -> height = 2;
	middle->transform_inverse = ft_inverse(ft_multi_matrices(
		ft_translate(0, 1, 0), ft_rotate_x(PI/2)));
	middle->material.color = ft_color(.1, 1, .5);
	middle->material.diffuse = .7;
	middle->material.specular = .3;


	t_obj	*sphere;

	sphere = ft_objnew(OT_SPHERE, NULL);
	sphere->material.color = ft_color(.3, 1, .1);
	sphere->transform_inverse = ft_inverse(ft_scale(1, 1.1, 1));
	sphere->material.diffuse = .7;
	sphere->material.specular = .3;


	// WORLD
	t_world		w;
	t_camera	camera;
	t_canvas	canvas;

	w.light = ft_point_light(ft_point(-10, 10, 10), ft_color(1, 1, 1));
	
	// Adding to world
	w.objlst = NULL;
	// ft_objadd_back(&w.objlst, wall);
	ft_objadd_back(&w.objlst, floor);
	// ft_objadd_back(&w.objlst, sphere);
	ft_objadd_back(&w.objlst, middle);

	camera = ft_camera(CANVAS_WIDTH, CANVAS_HEIGHT, PI/3);
	camera.view_transform_inverse = ft_view_transform_inverse(
		ft_point(-5, 3, 4), ft_normalize(ft_negv(ft_vector(-5, 3, 4))));// STOPPED HERE
	(void)canvas;
	canvas = ft_render(w, camera);
	// printf("The normalized (10, 10, 10) is: \n");
	// ft_print_tuple(ft_normalize(ft_vector(0, 1, -1)));
	ft_canvas_to_ppm(&canvas);
	// THERE IS A PROBLEM HERE, MAKE SURE TO CHECK IT
}

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
