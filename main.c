#include "minirt.h"

// int main()
// {
// 	t_ray		r;
// 	t_objnode 	*sph;
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
int main()
{
	t_objnode	*floor, *left_wall, *right_wall;

	// FLOOR
	floor = ft_objnew(OT_SPHERE);
	floor->transform_inverse = ft_inverse(ft_scale(10, .01, 10));
	floor->material.color = ft_color(1, .9, .9);
	floor->material.specular = 0;

	// LEFT WALL
	left_wall = ft_objnew(OT_SPHERE);
	left_wall->transform_inverse = ft_inverse(
		ft_multi_matrices(ft_translate(0, 0, 5),
			ft_multi_matrices(ft_rotate_y(-PI/4),
				ft_multi_matrices(ft_rotate_x(PI/2), ft_scale(10, .01, 10)))));
	left_wall->material = floor->material;

	// RIGHT WALL
	right_wall = ft_objnew(OT_SPHERE);
	right_wall->transform_inverse = ft_inverse(
		ft_multi_matrices(ft_translate(0, 0, 5),
			ft_multi_matrices(ft_rotate_y(PI/4),
				ft_multi_matrices(ft_rotate_x(PI/2), ft_scale(10, .01, 10)))));
	right_wall->material = floor->material;


	// SPHERES
	t_objnode	*middle, *right, *left;

	middle = ft_objnew(OT_SPHERE);
	middle->transform_inverse = ft_inverse(ft_translate(-.5, 1, .5));
	middle->material.color = ft_color(.1, 1, .5);
	middle->material.diffuse = .7;
	middle->material.specular = .3;

	right = ft_objnew(OT_SPHERE);
	right->transform_inverse = ft_inverse(ft_multi_matrices(
		ft_translate(1.5, .5, -.5), ft_scale(.5, .5, .5)
	));
	right->material.color = ft_color(.5, 1, .1);
	right->material.diffuse = .7;
	right->material.specular = .3;

	left = ft_objnew(OT_SPHERE);
	left->transform_inverse = ft_inverse(ft_multi_matrices(
		ft_translate(-1.5, .33, -.75), ft_scale(.33, .33, .33)
	));
	left->material.color = ft_color(1, .8, .1);
	left->material.diffuse = .7;
	left->material.specular = .3;

	// WORLD
	t_world		w;
	t_camera	camera;
	t_canvas	canvas;

	w.light = ft_point_light(ft_point(-10, 10, -10), ft_color(1, 1, 1));
	
	// Adding to world
	w.objlst = NULL;
	ft_objadd_back(&w.objlst, floor);
	ft_objadd_back(&w.objlst, left_wall);
	ft_objadd_back(&w.objlst, right_wall);
	ft_objadd_back(&w.objlst, middle);
	ft_objadd_back(&w.objlst, left);
	ft_objadd_back(&w.objlst, right);


	camera = ft_camera(CANVAS_WIDTH, CANVAS_HEIGHT, PI/3);
	camera.view_transform_inverse = ft_view_transform_inverse(
		ft_point(0, 1.5, -5), ft_point(0, 1, 0));
	(void)canvas;
	canvas = ft_render(w, camera);
	ft_canvas_to_ppm(&canvas);
}

