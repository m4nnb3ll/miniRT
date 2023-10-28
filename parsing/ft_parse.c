/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelayad <abelayad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 15:42:20 by abelayad          #+#    #+#             */
/*   Updated: 2023/10/28 20:53:41 by abelayad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// Check for s before passing it to this function
enum e_el_type	ft_get_el_type(char *s)
{
	if (s[0] == 'C' && s[1] == ' ')
		return (EL_TYPE_C);
	if (s[0] == 'l' && s[1] == ' ')//should be atleast one
		return (EL_TYPE_L);
	if (s[0] == 's' && s[1] == 'p' && s[2] == ' ')
		return (EL_TYPE_SP);
	if (s[0] == 'p' && s[1] == 'l' && s[2] == ' ')
		return (EL_TYPE_PL);
	if (s[0] == 'c' && s[1] == 'y' && s[2] == ' ')
		return (EL_TYPE_CY);
	if (s[0] == 'c' && s[1] == 'n' && s[2] == ' ')
		return (EL_TYPE_CN);
	return (EL_TYPE_ERR);
}

bool	ft_get_color(char **s, t_color *c)
{
	char	**tuple_split;

	ft_skip_spaces(s); // skip any possible leading spaces
	if (!ft_color_check(*s)) return (false);
	ft_tmp_sp_truncate_str(*s, 0);
	tuple_split = ft_split(*s, ',');
	ft_tmp_sp_truncate_str(*s, 1);
	if (!tuple_split || ft_get_strs_count(tuple_split) != 3
		|| !ft_get_color_channel_converted(&(c->r), tuple_split[0])
		|| !ft_get_color_channel_converted(&(c->g), tuple_split[1])
		|| !ft_get_color_channel_converted(&(c->b), tuple_split[2]))
		return (false);
	ft_free_char2(tuple_split);
	ft_skip_token_space(s, 0);
	return (true);
}

bool	ft_get_tuple(char **s, t_tuple *t, bool is_pt)
{
	char	**tuple_split;

	ft_skip_spaces(s); // skip any possible leading spaces
	if (!ft_tuple_check(*s)) return (false);
	ft_tmp_sp_truncate_str(*s, 0);
	tuple_split = ft_split(*s, ',');
	ft_tmp_sp_truncate_str(*s, 1);
	if (!tuple_split) return (false);
	if (ft_get_strs_count(tuple_split) != 3) return (false);
	t -> x = atof(tuple_split[0]);
	t -> y = atof(tuple_split[1]);
	t -> z = atof(tuple_split[2]);
	t -> w = is_pt;
	ft_free_char2(tuple_split);
	ft_skip_token(s);
	return (true);
}

bool	ft_get_double(char **s, double *fov)
{
	char	*start;

	ft_skip_spaces(s); // skip any possible leading spaces
	ft_tmp_sp_truncate_str(*s, 0);
	start = *s;
	while (**s && (ft_isdigit(**s) || **s == '.'))
		(*s)++;
	if (**s) return (false);
	*fov = atof(start);
	ft_tmp_sp_truncate_str(*s, 1);
	return (true);
}

// Check if the line ends with a new line\n
bool	ft_get_camera(char *s, t_world *w)
{
	ft_skip_token(&s); // skip type
	if (!ft_get_tuple(&s, &w->camera.from, true)
		|| !ft_get_tuple(&s, &w->camera.to, true)
		|| !ft_get_double(&s, &w->camera.fov))
		return (false);
	w->camera.set = true;
	return (!*s);
}

// It doesn't seem to throw an error when big L
// Check it out later
bool	ft_get_light(char *s, t_world *w)
{
	t_light	tmp_light;
	t_light	*light;

	ft_skip_token(&s); // skip type
	if (!ft_get_tuple(&s, &tmp_light.position, true)
		|| !ft_get_color(&s, &tmp_light.color))
		return (false);
	if (*s) return (false);
	light = ft_lightnew(tmp_light.position, tmp_light.color);
	if (!light) return (false);
	return (ft_lightadd_back(&w->light_lst, light), true);
}

bool	ft_get_optional_obj_params(char **s, t_obj *o)
{
	ft_skip_spaces(s); // skip any possible leading spaces
	ft_tmp_sp_truncate_str(*s, 0);
	o -> checkered = !ft_strcmp(*s, "1");
	ft_tmp_sp_truncate_str(*s, 1);
	ft_skip_token_space(s, 0);
	if (!**s) return (true); // if there is no more, return
	ft_tmp_sp_truncate_str(*s, 0);
	if (ft_strcmp(*s, "0") != 0)
		o -> tex = ft_png_img_to_tex(ft_read_png_file(*s));
	ft_tmp_sp_truncate_str(*s, 1);
	ft_skip_token_space(s, 0);
	if (!**s) return (true);
	ft_tmp_sp_truncate_str(*s, 0);
	if (ft_strcmp(*s, "0") != 0)
		o -> btex = ft_png_img_to_tex(ft_read_png_file(*s));
	ft_tmp_sp_truncate_str(*s, 1);
	ft_skip_token_space(s, 0);
	return (!**s);
}

bool	ft_get_sp(char *s, t_world *w)
{
	t_obj		*o;
	t_tuple		pt;
	double		d;

	ft_skip_token(&s); // skip type
	o = ft_objnew(OT_SPHERE);
	if (!ft_get_tuple(&s, &pt, true)
		|| !ft_get_double(&s, &d)
		|| !ft_get_color(&s, &o->material.color)
		|| !ft_get_optional_obj_params(&s, o))
		return (false);
	// d / 2, because the default sphere is of radius 1.
	o -> transform_inverse = ft_inverse(
		ft_multi_matrices(
			ft_translate(pt.x, pt.y, pt.z),
			ft_scale(d / 2, d / 2, d / 2)
			)
		);
	/*glass test*/
	// o->material.reflective = .1;
	if (!o->material.color.r && !o->material.color.g && !o->material.color.b)
	{
		o->material.transparency = .8;
		o->material.ri = GLASS;
	}

	/*glass test end*/
	ft_objadd_back(&w->obj_lst, o);
	return (true);
}

bool	ft_get_pl(char *s, t_world *w)
{
	t_obj		*o;
	t_tuple		pt;
	t_tuple		normal;

	ft_skip_token(&s); // skip type
	o = ft_objnew(OT_PLANE);
	if (!ft_get_tuple(&s, &pt, true)
		|| !ft_get_tuple(&s, &normal, false)
		|| !ft_get_color(&s, &o->material.color)
		|| !ft_get_optional_obj_params(&s, o))
		return (false);
	o -> transform_inverse = ft_inverse(
		ft_multi_matrices(
			ft_translate(pt.x, pt.y, pt.z),
			ft_get_rotation_matrix(ft_vector(0, 0, 1), normal)
			)
		);
	// test
	if (o->btex.height || o -> checkered)
		o -> material.reflective = .3;
	// test end
	ft_objadd_back(&w->obj_lst, o);
	return (true);
}

bool	ft_get_cycone(char *s, t_world *w, enum e_el_type el_type)
{
	t_obj	*o;
	t_tuple	pt;
	t_tuple	dir_v;
	double	d;
	double	h;

	ft_skip_token(&s); // skip type
	o = ft_objnew(el_type == EL_TYPE_CY ? OT_CYLINDER : OT_CONE);
	if (!ft_get_tuple(&s, &pt, true)
		|| !ft_get_tuple(&s, &dir_v, false)
		|| !ft_get_double(&s, &d)
		|| !ft_get_double(&s, &h)
		|| !ft_get_color(&s, &o->material.color)
		|| !ft_get_optional_obj_params(&s, o))
		return (false);
	// to be tested later
	o -> transform_inverse = ft_inverse(
		ft_multi_matrices(
			ft_translate(pt.x, pt.y, pt.z),
			ft_multi_matrices(
				ft_get_rotation_matrix(ft_vector(0, 1, 0), dir_v),
				ft_scale(d, h, d)
				)
			)
		);
	ft_objadd_back(&w->obj_lst, o);
	return (true);
}

bool	ft_extract_el(char *s, t_world *w)
{
	enum e_el_type	type;

	type = ft_get_el_type(s);
	switch (type)
	{
		case (EL_TYPE_C):
			return (ft_get_camera(s, w));
		case (EL_TYPE_L):
			return (ft_get_light(s, w));
		case (EL_TYPE_SP):
			return (ft_get_sp(s, w));
		case (EL_TYPE_PL):
			return (ft_get_pl(s, w));
		case (EL_TYPE_CY):
		case (EL_TYPE_CN):
			return (ft_get_cycone(s, w, type));
		default:
			return (false);
	}
}

char	*ft_nullify_nl(char *s)
{
	size_t	len;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	if (s[len - 1] == '\n')
		s[len - 1] = 0;
	return (s);
}

/*
char	*str_types[] = {
			"Camera",
			"Light",
			"Sphere",
			"Plane",
			"Cylinder",
			"Cone",
			"Error"
		};
*/

t_world	ft_parse_rt_file(char *filename)
{
	int			fd;
	t_world		world;
	char		*line;

	ft_bzero(&world, sizeof(t_world));
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		(printf("Error opening the file"), exit(-42));
	line = ft_nullify_nl(get_next_line(fd));
	while (line)
	{
		if (*line != '#' &&  !ft_extract_el(line, &world))
			(printf("ERROR IN FILE FORMAT: `%s`\n", line), exit(-42));
		free(line);
		line = ft_nullify_nl(get_next_line(fd));
	}
	if (!world.camera.set || !world.light_lst)
		exit(printf("%sCamera or Light is missing!!!%s\n", RED, RESET_COLOR));
	world.camera = ft_camera(world.camera);
	return (world);
}