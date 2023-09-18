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
	ft_print_color(m.color);
	printf("%f %f %f %f\n", m.ambient, m.diffuse, m.specular, m.shininess);
}

void	ft_print_obj(t_obj *obj)
{
	// Type
	printf("the obj type is: %s\n", objs_strs[obj->type]);
	// Transform Inverse
	printf("The transform_inverse is:\n");
	ft_print_matrix(obj->transform_inverse);
	// Material
	printf("The material is:\n");
	ft_print_material(obj->material);
	printf("The props are: %p\n", obj->props);
}
void set_background(mlx_image_t	*image, int width, int height);
int main(/* int argc, char **argv */)
{
	// t_canvas	canvas;
	t_world		w;

	// if (argc != 2)
		// return (printf("usage: ./miniRT <file>\n"));
	world_data(&w, "test.rt");
	// printf("The object type is: %s\n", objs_strs[w.objs[0].type]);
	w.objs[0].transform_inverse = ft_inverse(ft_translate(1, 0, 0));
	// w.objs[0].transform_inverse = g_identity_matrix;
	w.objs[0].material = ft_material();
	// w.objs[0].material.color = g_red;
	w.objs[0].checkered = true;
	w.camera = ft_camera(w.camera);
	// ft_print_obj(&w.objs[0]);
	t_window window = ft_img_ptr();
	ft_render(window, &w, w.camera);
	// ft_canvas_to_ppm(&canvas);
	// execv("/usr/bin/open", (char*[]){"/usr/bin/open", "test.ppm"});
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

// int main(int argc, char **argv)
// {
// 	t_world	w;

// 	if (argc != 2)
// 		return (printf("usage: ./miniRT <file>\n"));
// 	(void)argc;
// 	world_data(&w, argv[1]);
// 	ft_print_ambient(w.ambient);
// 	ft_print_camera(w.camera);

// }