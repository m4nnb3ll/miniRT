#include "minirt.h"

// int main()
// {
// 	t_ray		r;
// 	t_obj 	*sph;
// 	t_xnode		*i;
// 	t_comps		comps;
// 	char		*bools[2] = { FALSE_S, TRUE_S };

// 	r = ft_ray(ft_point(0, 0, -5), ft_vector(0, 0, 1));
// 	sph = ft_objnew(OT_SPHERE);
// 	sph -> transform_inverse = ft_inverse(ft_translate(0, 0, 1));
// 	i = ft_xnew(sph, 5);
// 	comps = ft_prepare_comps(r, i);
// 	printf("comps.over_pt.z is: %f\n", comps.over_pt.z);
// 	printf("-EPSILON/2 is: %f\n", -EPSILON/2);
// 	printf("comps.over_pt.z < -EPSILON/2: %s\n", bools[comps.over_pt.z < -EPSILON/2]);
// 	printf("comps.pt.z > comps.over_pt.z: %s\n", bools[comps.pt.z > comps.over_pt.z]);
// }

// FINAL MAIN BELOW
// int main()
// {
// 	t_obj	*floor, *left_wall, *right_wall;

// 	// FLOOR
// 	floor = ft_objnew(OT_PLANE);
// 	floor -> transform_inverse = ft_inverse(ft_rotate_y(PI/2));
// 	floor->material.color = ft_color(1, 1, 1);
// 	floor->material.specular = 0;

// 	// LEFT WALL
// 	left_wall = ft_objnew(OT_SPHERE);
// 	left_wall->transform_inverse = ft_inverse(
// 		ft_multi_matrices(ft_translate(0, 0, 5),
// 			ft_multi_matrices(ft_rotate_y(-PI/4),
// 				ft_multi_matrices(ft_rotate_x(PI/2), ft_scale(10, .01, 10)))));
// 	left_wall->material = floor->material;

// 	// RIGHT WALL
// 	right_wall = ft_objnew(OT_SPHERE);
// 	right_wall->transform_inverse = ft_inverse(
// 		ft_multi_matrices(ft_translate(0, 0, 5),
// 			ft_multi_matrices(ft_rotate_y(PI/4),
// 				ft_multi_matrices(ft_rotate_x(PI/2), ft_scale(10, .01, 10)))));
// 	right_wall->material = floor->material;


// 	// SPHERES
// 	t_obj	*middle, *right, *left;

// 	middle = ft_objnew(OT_SPHERE);
// 	middle->transform_inverse = ft_inverse(ft_translate(-.5, 1, .5));
// 	middle->material.color = ft_color(.1, 1, .5);
// 	middle->material.diffuse = .7;
// 	middle->material.specular = .3;

// 	right = ft_objnew(OT_SPHERE);
// 	right->transform_inverse = ft_inverse(ft_multi_matrices(
// 		ft_translate(1.5, .5, -.5), ft_scale(.5, .5, .5)
// 	));
// 	right->material.color = ft_color(.5, 1, .1);
// 	right->material.diffuse = .7;
// 	right->material.specular = .3;

// 	left = ft_objnew(OT_SPHERE);
// 	left->transform_inverse = ft_inverse(ft_multi_matrices(
// 		ft_translate(-1.5, .33, -.75), ft_scale(.33, .33, .33)
// 	));
// 	left->material.color = ft_color(1, .8, .1);
// 	left->material.diffuse = .7;
// 	left->material.specular = .3;

// 	// WORLD
// 	t_world		w;
// 	t_camera	camera;
// 	t_canvas	canvas;

// 	w.light = ft_point_light(ft_point(0, 10, 0), ft_color(1, 1, 1));
	
// 	// Adding to world
// 	w.objlst = NULL;
// 	ft_objadd_back(&w.objlst, floor);
// 	// ft_objadd_back(&w.objlst, left_wall);
// 	// ft_objadd_back(&w.objlst, right_wall);
// 	ft_objadd_back(&w.objlst, middle);
// 	ft_objadd_back(&w.objlst, left);
// 	ft_objadd_back(&w.objlst, right);


// 	camera = ft_camera(CANVAS_WIDTH, CANVAS_HEIGHT, PI/3);
// 	camera.view_transform_inverse = ft_view_transform_inverse(
// 		ft_point(0, 10, -10), ft_point(0, 1, 0));
// 	(void)canvas;
// 	canvas = ft_render(w, camera);
// 	ft_canvas_to_ppm(&canvas);
// }



// int main()
// {
// 	t_obj	*floor;

// 	// FLOOR
// 	t_plane	*pl = ft_calloc(1, sizeof(t_plane));
// 	floor = ft_objnew(OT_PLANE, pl);
// 	((t_plane*)(floor -> props)) -> normal = ft_vector(0, 1, 0);
// 	((t_plane*)(floor -> props)) -> pt = ft_point(0, 0, 0);
// 	floor->material.color = ft_color(1, 1, 1);
// 	// floor->material.specular = 0;

// 	// wall
// 	pl = ft_calloc(1, sizeof(t_plane));
// 	t_obj	*wall = ft_objnew(OT_PLANE, pl);
// 	((t_plane*)(wall -> props)) -> normal = ft_vector(0, 0, 1);
// 	((t_plane*)(wall -> props)) -> pt = ft_point(0, 0, 3);
// 	wall->material.color = ft_color(1, 1, 0);
// 	// wall->material.specular = 0;

// 	// SPHERES
// 	t_obj	*middle;

// 	middle = ft_objnew(OT_SPHERE, NULL);
// 	middle->transform_inverse = ft_inverse(ft_translate(-.5, 1, .5));
// 	middle->material.color = ft_color(.1, 1, .5);
// 	middle->material.diffuse = .7;
// 	middle->material.specular = .3;

// 	// WORLD
// 	t_world		w;
// 	t_camera	camera;
// 	t_canvas	canvas;

// 	w.light = ft_point_light(ft_point(-10, 10, -10), ft_color(1, 1, 1));
	
// 	// Adding to world
// 	w.objlst = NULL;
// 	ft_objadd_back(&w.objlst, wall);
// 	ft_objadd_back(&w.objlst, floor);
// 	ft_objadd_back(&w.objlst, middle);

// 	camera = ft_camera(CANVAS_WIDTH, CANVAS_HEIGHT, PI/3);
// 	camera.view_transform_inverse = ft_view_transform_inverse(
// 		ft_point(0, 1, -10), ft_vector(0, 0, 1));
// 	(void)canvas;
// 	canvas = ft_render(w, camera);
// 	ft_canvas_to_ppm(&canvas);
// }

// t_matrix

int main()
{
	// t_tuple		a, b, v;
	// double		s, c;
	// t_matrix	vx;
	// t_matrix	vx2;
	// t_matrix	final;
 
	// a = ft_normalize(ft_vector(-3.4, 6.1, 1.4));
	// b = ft_normalize(ft_vector(7.1, 2.3, 4.1));
	// v = ft_normalize(ft_cross(a, b));
	// s = ft_mag(v);
	// c = ft_dot(a, b);
	// vx = (t_matrix){3, {
	// 	{0, -v.z, v.y, 0},
	// 	{v.z, 0, -v.x, 0},
	// 	{-v.y, v.x, 0, 0},
	// 	{0, 0, 0, 1}
	// }};

	// vx2 = ft_multi_matrices(vx, vx);
	// // printf("The vx2 matrix is:\n");
	// // ft_print_matrix(vx2);
	// vx2 = ft_matrix_scl(vx2, (1-c)/pow(s, 2));
	// final = ft_add_matrices(ft_add_matrices(vx, vx2), g_identity_matrix);
	// // printf("The transformation matrix is:\n");
	// // ft_print_matrix(final);
	// printf("The transformed vector is:\n");
	// ft_print_tuple(ft_transform_tuple(final, a));
	// printf("b normalized is:\n");
	// ft_print_tuple(b);

	/* ---------------------------------------------------- */

	t_tuple     v1, v2;
    t_matrix    m;

    v1 = ft_normalize(ft_vector(.341, 1.142, .69420));
    v2 = ft_normalize(ft_vector(54.4150, 3.1574, 25.124));
    m = ft_get_rotation_matrix(v1, v2);
	printf("The matrix is:\n");
	ft_print_matrix(m);
    printf("The transformed v1 is:\n");
    ft_print_tuple(ft_transform_tuple(m, v1));
    printf("V2 is:\n");
    ft_print_tuple(v2);
}
