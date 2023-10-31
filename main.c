/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelayad <abelayad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 16:09:43 by abelayad          #+#    #+#             */
/*   Updated: 2023/10/31 15:53:03 by abelayad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// u & v [0-1.0]
t_color	ft_uv_pattern_at(t_tex texture, double u, double v)
{
	int	x;
	int	y;

	if (!texture.pixels)
	{
		// printf("I return black from here 1\n");
		return (g_black);
	}
	x = (int)floor(u * (texture.width)) % texture.width;
	y = (int)floor(v * (texture.height)) % texture.height;
	return (texture.pixels[y][x]);
}

// take only the x and y
t_tuple	ft_planar_map(t_tuple op)
{
	return ((t_tuple){fabs(fmod(op.x, 1)), fabs(fmod(op.y, 1)), 0, 0});
}


// t_world	ft_default_world(void)
// {
// 	t_world	w;

// 	ft_bzero(&w, sizeof(t_world));
// 	w.num_objs = 2;
// 	w.num_lights = 1;
// 	w.lights[0].position = ft_point(-10, 10, -10);
// 	w.lights[0].color = ft_color(1, 1, 1);
// 	w.objs = ft_calloc(w.num_objs, sizeof(t_obj));
// 	// SPHERE A
// 	w.objs[0].type = OT_SPHERE;
// 	w.objs[0].transform_inverse = g_identity_matrix;
// 	w.objs[0].material = ft_material();
// 	w.objs[0].material.ambient = 1;
// 	w.objs[0].material.color = ft_color(.8, 1, .6);
// 	w.objs[0].material.transparency = 0;
// 	w.objs[0].material.reflective = 0;
// 	w.objs[0].checkered = true;
// 	// SPHERE B
// 	w.objs[1].type = OT_SPHERE;
// 	w.objs[1].material = ft_material();
// 	w.objs[1].transform_inverse = ft_inverse(ft_scale(0.5, 0.5, 0.5));
// 	return (w);
// }
/*
w.objs[0].type = OT_PLANE;
	w.objs[0].material = ft_material();
	w.objs[0].material.reflective = 1;
	w.objs[0].transform_inverse = ft_inverse(ft_translate(0, -1, 0));
	w.objs[1].type = OT_PLANE;
	w.objs[1].material = ft_material();
	w.objs[1].material.reflective = 1;
*/

t_color	ft_reflected_color(t_world *w, t_comps c, int remaining)
{
	t_ray	reflect_ray;
	t_color	color;

	ft_bzero(&reflect_ray, sizeof(t_ray));
	ft_bzero(&color, sizeof(t_color));
	// (void)w;
	// (void)c;
	if (!c.o->material.reflective || remaining <= 0)
	{
		// printf("I return black from here 2\n");
		return (g_black);
	}
	reflect_ray = ft_ray(c.over_pt, c.rv);
	// ft_print_ray(reflect_ray);
	color = ft_color_at(w, reflect_ray, remaining - 1);
	return (ft_color_scl(color, c.o->material.reflective));
}

// Function to perform Bubble Sort on the linked list
t_xnode	*ft_sort_xs(t_xnode *head)
{
	t_xnode	swap;
	t_xnode	*tmp;

	if (!head)
		return (head);
	tmp = head;
    while (tmp && tmp -> next)
	{
		if (tmp->next->x < tmp->x)
		{
			swap = *tmp;
			tmp->x = tmp->next->x;
			tmp->o = tmp->next->o;
			tmp->next->x = swap.x;
			tmp->next->o = swap.o;
			tmp = head;
			continue ;
		}
		tmp = tmp -> next;
    }
	return (head);
}

void	ft_print_container(t_contnode *head)
{
	printf("The containers are:\n");
	while (head)
	{
		printf("%p\n", head->o);
		head = head -> next;
	}
}

void	ft_clear_containers(t_contnode	**contlst)
{
	t_contnode	*tmp;
	t_contnode	*next;

	if (!contlst || !*contlst)
		return ;
	tmp = *contlst;
	while (tmp)
	{
		next = tmp -> next;
		free(tmp);
		tmp = next;
	}
	*contlst = NULL;
}

void	ft_get_ns(t_xnode *hit, t_xnode *xs, t_comps *comps)
{
	t_contnode	*contlst;

	contlst = NULL;
	while (xs)
	{
		// printf("The ri of the xs is: %f\n", xs->o->material.ri);
		// printf("Loop\n");
		if (xs == hit)
		{
			if (!contlst)
			{
				// printf("1\n");
				comps->ns[0] = VACUUM;
			}
			else
			{
				// printf("2\n");
				// printf("The ri of the object of the interseciton is: %f\n", xs->o->material.ri);
				comps->ns[0] = ft_containers_last(contlst)->o->material.ri;
			}
		}
		if (ft_containers_contain(contlst, xs->o))
		{
			// printf("the object ri is: %f\n", xs->o->material.ri);
			// printf("3\n");
			// printf("The ri of the object that going to be removed is: %f\n", xs->o->material.ri);
			ft_remove_container(&contlst, xs->o);
		}
		else
		{
			// printf("4\n");
			ft_contadd_back(&contlst, ft_contnew(xs->o));
		}
		if (xs == hit)
		{
			if (!contlst)
			{
				// printf("5\n");
				comps->ns[1] = VACUUM;
			}
			else
			{
				// printf("6\n");
				comps->ns[1] = ft_containers_last(contlst)->o->material.ri;
				// ft_print_container(contlst);
				// printf("ft_containers_last(contlst) is: %p\n", ft_containers_last(contlst));
				// printf("ft_containers_last(contlst)->o->material.ri is: %f\n", ft_containers_last(contlst)->o->material.ri);
				// comps->ns[1] = ;
			}
			break ;
		}
		xs = xs -> next;
	}
	ft_clear_containers(&contlst);
}

// int	main(void)
// {
// 	t_world	w;
// 	t_ray	r;
// 	t_xnode	*xs;
// 	t_comps	comps;

// 	w = ft_default_world();
// 	r = ft_ray(ft_point(0, 0, -4), ft_vector(0, 0, 1));
// 	xs = NULL;
// 	ft_xadd_back(&xs, ft_xnew(&w.objs[0], 2));
// 	ft_xadd_back(&xs, ft_xnew(&w.objs[1], 2.75));
// 	ft_xadd_back(&xs, ft_xnew(&w.objs[2], 3.25));
// 	ft_xadd_back(&xs, ft_xnew(&w.objs[1], 4.75));
// 	ft_xadd_back(&xs, ft_xnew(&w.objs[2], 5.25));
// 	ft_xadd_back(&xs, ft_xnew(&w.objs[0], 6));
// 	comps = ft_prepare_comps(r, xs, xs);
// 	printf("comps n1,n2 are: %f,%f\n", comps.ns[0], comps.ns[1]);
// 	comps = ft_prepare_comps(r, xs->next, xs);
// 	printf("comps n1,n2 are: %f,%f\n", comps.ns[0], comps.ns[1]);
// 	comps = ft_prepare_comps(r, xs->next->next, xs);
// 	printf("comps n1,n2 are: %f,%f\n", comps.ns[0], comps.ns[1]);
// 	// STOPPED BELOW
// 	comps = ft_prepare_comps(r, xs->next->next->next, xs);
// 	printf("comps n1,n2 are: %f,%f\n", comps.ns[0], comps.ns[1]);
// 	comps = ft_prepare_comps(r, xs->next->next->next->next, xs);
// 	printf("comps n1,n2 are: %f,%f\n", comps.ns[0], comps.ns[1]);
// 	comps = ft_prepare_comps(r, xs->next->next->next->next->next, xs);
// 	printf("comps n1,n2 are: %f,%f\n", comps.ns[0], comps.ns[1]);
// }

// GO BACK TO PAGE 157

t_color	ft_refracted_color(t_world *w, t_comps comps, int remaining)
{
	double	n_ratio;
	double	cos_it[2];
	double	sin_t_2;
	t_tuple	direction;
	t_ray	refract_ray;

	n_ratio = 0;
	ft_bzero(&cos_it, sizeof(cos_it));
	sin_t_2 = 0;
	ft_bzero(&direction, sizeof(t_tuple));
	ft_bzero(&refract_ray, sizeof(t_ray));
	if (remaining <= 0)
	{
		// printf("I RETURN 111!!!");
		return (g_black);
	}
	if (!comps.o->material.transparency)
	{
		// printf("I RETURN 222!!!");
		return (g_black);
	}
	// printf("I PASS to<<<<,\n");
	n_ratio = comps.ns[0] / comps.ns[1];
	cos_it[0] = ft_dot(comps.ev, comps.nv);
	sin_t_2 = pow(n_ratio, 2) * (1 - pow(cos_it[0], 2));
	if (sin_t_2 > 1)
		return (g_black);
	cos_it[1] = sqrt(1 - sin_t_2);
	direction = ft_sub_tuples(ft_sclv(comps.nv, n_ratio * cos_it[0] - cos_it[1]),
					ft_sclv(comps.ev, n_ratio));
	refract_ray = ft_ray(comps.under_pt, direction);
	// printf("There is a color returned\n");
	return (ft_color_scl(ft_color_at(w, refract_ray, remaining - 1),
				comps.o->material.transparency));
}

// int	main(void)
// {
// 	t_ray		r;
// 	t_xnode		*xs;
// 	t_comps		comps;
// 	t_obj	obj;

// 	r = ft_ray(ft_point(0, 0, -5), ft_vector(0, 0, 1));
// 	// SPHERE A
// 	obj.type = OT_SPHERE;
// 	obj.transform_inverse = ft_inverse(ft_translate(0, 0, 1));
// 	obj.material = ft_material();
// 	xs = NULL;
// 	ft_xadd_back(&xs, ft_xnew(&obj, 5));
// 	comps = ft_prepare_comps(r, xs, xs);
// 	printf("The comps.under_point.z > EPSILON/2 is: %d\n", comps.under_pt.z > EPSILON/2);
// 	printf("The comps.point.z < comps.under_point.z is: %d\n", comps.pt.z < comps.under_pt.z);
// }

// int main(void)
// {
// 	t_world	w;
// 	t_ray	r;
// 	t_xnode	*xs;
// 	t_comps	comps;
// 	t_color	color;

// 	w = ft_default_world();
// 	// w.objs[0].material.transparency = 0;
// 	r = ft_ray(ft_point(0, 0, sqrt(2)/2), ft_vector(0, 1, 0));
// 	xs = NULL;
// 	ft_xadd_back(&xs, ft_xnew(&w.objs[0], -sqrt(2)/2));
// 	ft_xadd_back(&xs, ft_xnew(&w.objs[0], sqrt(2)/2));
// 	comps = ft_prepare_comps(r, xs->next, xs);
// 	color = ft_refracted_color(&w, comps, 5);
// 	printf("The refracted color is:\n");
// 	ft_print_color(color);
// }

typedef struct	s_chunk
{
	t_png_img	*img;
	t_world		*w;
	int			num;
	pthread_t	thread;
}	t_chunk;

// pthread_mutex_t test = PTHREAD_MUTEX_INITIALIZER;

void	*ft_render_wrapper(void *arg)
{
	t_chunk *chunk = arg;

	ft_render(chunk->img, chunk->w, chunk->num);
	return (NULL);
}


int	main(int argc, char **argv)
{
	t_world		w;
	// t_window	window;
	t_png_img	img;


	if (argc != 2)
		return (printf("Please provide a scene file!\n"), -42);
	// world_data(&w, argv[1]);
	// w.camera = ft_camera(w.camera);
	// window = ft_img_ptr();
	img = ft_allocate_png_img(SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!img.row_pointers)
		return (printf("Error allocating the image\n"), -42);
	w = ft_parse_rt_file(argv[1]);
	// printf("The worldss light is at: ");
	// ft_print_tuple(w.light_lst->position);

	/*
	t_png_img	*img;
	t_world		*w;
	int			num;
	*/

	t_chunk	chunks[w.cores_cnt];
	for (int i=0; i < w.cores_cnt; i++)
	{
		chunks[i].img = &img;
		chunks[i].w = &w;
		chunks[i].num = i;
	}
	
	for (int i=0; i < w.cores_cnt; i++)
	{
		if (pthread_create(&chunks[i].thread, NULL, ft_render_wrapper, &chunks[i]) != 0)
			(perror("pthread_create"), exit(2));
		// wrapper.phase++;
		// usleep(69);
	}

	for (int i=0; i < w.cores_cnt; i++)
		pthread_join(chunks[i].thread, NULL);

	ft_write_png_file("scene.png", img);

	// ft_render(img, &w, w.camera);
}
