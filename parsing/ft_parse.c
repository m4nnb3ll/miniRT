/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelayad <abelayad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 15:42:20 by abelayad          #+#    #+#             */
/*   Updated: 2023/09/26 22:53:45 by abelayad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"


void	ft_print_tuple(t_tuple t)
{
	printf(">>%f %f %f %f<<\n", t.x, t.y, t.z, t.w);
}

void	ft_print_color(t_color c)
{
	printf(">>%f %f %f<<\n", c.r, c.g, c.b);
}

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
	printf("s[0] s[1]: %c %c  \n", s[0], s[1]);
	return (EL_TYPE_ERR);
}

// typedef struct s_world
// {
// 	t_ambient	ambient;
// 	t_camera	camera;
// 	t_light		lights[2];
// 	t_obj		*objs;
// 	int			num_objs;
// 	int			num_lights;
// }	t_world_tst;

// typedef struct s_camera
// {
// 	t_tuple	from;
// 	t_tuple	to;
// 	int		fov;
// 	// int			screen_w;
// 	// int			screen_h;
// 	// double		psize;
// 	// double		half_c_w;
// 	// double		half_c_h;
// 	// t_matrix	view_transform_inverse;
// }	t_camera;

void	ft_skip_spaces(char **s)
{
	while (**s && isspace(**s))
		(*s)++;
}

bool	ft_tuple_check(char *s)
{
	int	i;
	int	comma;

	i = 0;
	comma = 0;
	while (s[i]
		&& (s[i] == '.' || s[i] == ',' || s[i] == '-' || ft_isdigit(s[i])))
	{
		if (s[i] == ',')
			comma++;
		i++;
	}
	return ((!s[i] || isspace(s[i])) && comma == 2);
}

bool	ft_color_check(char *s)
{
	int	i;
	int	comma;

	i = 0;
	comma = 0;
	while (s[i] && (s[i] == ',' || ft_isdigit(s[i])))
	{
		if (s[i] == ',')
			comma++;
		i++;
	}
	return ((!s[i] || isspace(s[i])) && comma == 2);
}

int	ft_get_strs_count(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
		i++;
	return (i);
}

void	ft_tmp_sp_truncate_str(char *s, bool reverse)
{
	int			i;
	static char	*p;
	
	if (reverse && p)
	{
		i = 0;
		while (s[i])
			i++;
		if (p == &s[i])
		{
			s[i] = ' ';
			p = NULL;
		}
	}
	else
	{
		i = 0;
		while (s[i])
		{
			if (s[i] == ' ')
			{
				s[i] = 0;
				p = &s[i];
				break ;
			}
			i++;
		}
	}
}

bool	ft_get_tuple(char **s, t_tuple *t, bool is_pt)
{
	char	**tuple_split;

	if (!ft_tuple_check(*s))
		return (false);
	ft_tmp_sp_truncate_str(*s, 0);
	tuple_split = ft_split(*s, ',');
	ft_tmp_sp_truncate_str(*s, 1);
	if (!tuple_split)
		return (false);
	if (ft_get_strs_count(tuple_split) != 3)
		return (false);
	t -> x = atof(tuple_split[0]);
	t -> y = atof(tuple_split[1]);
	t -> z = atof(tuple_split[2]);
	t -> w = is_pt;
	ft_free_char2(tuple_split);
	while (**s && **s != ' ')
		(*s)++;
	return (true);
}

bool	ft_get_color_channel_converted(double *channel, char *chan_str)
{
	int	i;

	i = 0;
	while (chan_str[i] && i < 4)
	{
		if (!ft_isdigit(chan_str[i]) && i <= 2)
			return (false);
		i++;
	}
	if (!(i >= 1 && i <= 3))
		return (false);
	*channel = atoi(chan_str); // to be converted later
	return (*channel >= 0 && *channel <= 255);
}

bool	ft_get_color(char **s, t_color *c)
{
	char	**tuple_split;

	if (!ft_color_check(*s))
		return (false);
	ft_tmp_sp_truncate_str(*s, 0);
	tuple_split = ft_split(*s, ',');
	ft_tmp_sp_truncate_str(*s, 1);
	if (!tuple_split || ft_get_strs_count(tuple_split) != 3
		|| !ft_get_color_channel_converted(&(c->r), tuple_split[0])
		|| !ft_get_color_channel_converted(&(c->g), tuple_split[1])
		|| !ft_get_color_channel_converted(&(c->b), tuple_split[2]))
		return (false);
	ft_free_char2(tuple_split);
	while (**s && **s != ' ')
		(*s)++;
	return (true);
}

bool	ft_get_double(char **s, double *fov)
{
	char	*start;

	start = *s;
	while (**s && ft_isdigit(**s))
		(*s)++;
	if (**s)
		return (false);
	*fov = atof(start);
	return (true);
}

// Check if the line ends with a new line\n
bool	ft_get_camera(char *s, t_world_tst *w)
{
	s++;
	ft_skip_spaces(&s);
	ft_get_tuple(&s, &w->camera.from, true);
	ft_skip_spaces(&s);
	ft_get_tuple(&s, &w->camera.to, true);
	ft_skip_spaces(&s);
	ft_get_double(&s, &w->camera.fov);
	ft_skip_spaces(&s);
	if (*s)
		return (false);
	return (true);
}

bool	ft_get_light(char *s, t_world_tst *w)
{
	t_light	tmp_light;
	t_light	*light;

	s++;
	ft_skip_spaces(&s);
	ft_get_tuple(&s, &tmp_light.position, true);
	ft_skip_spaces(&s);
	ft_get_color(&s, &tmp_light.color);
	ft_skip_spaces(&s);
	if (*s)
		return (false);
	light = ft_lightnew(tmp_light.position, tmp_light.color);
	if (!light)
		return (false);
	return (ft_lightadd_back(&w->light_lst, light), true);
}

// typedef struct s_sphere
// {
// 	t_tuple	pt;
// 	float	d;
// }	t_sphere;

void	ft_skip_word(char **s)
{
	while (**s && (ft_isalnum(**s) || **s == '.' || **s == '_'))
		(*s)++;
}

void	ft_skip_word_space(char **s, bool space_first)
{
	if (space_first)
	{
		ft_skip_spaces(s);
		ft_skip_word(s);
	}
	else
	{
		ft_skip_word(s);
		ft_skip_spaces(s);
	}
}

void	ft_get_optional_obj_params(char **s, t_obj *o)
{
	ft_tmp_sp_truncate_str(*s, 0);
	o -> tex = ft_png_img_to_tex(ft_read_png_file(*s));
	ft_tmp_sp_truncate_str(*s, 1);
	ft_skip_word_space(s, 0);
	if (!**s)
		return ;
	ft_tmp_sp_truncate_str(*s, 0);
	o -> btex = ft_png_img_to_tex(ft_read_png_file(*s));//exit on error
	ft_tmp_sp_truncate_str(*s, 1);
	ft_skip_word_space(s, 0);
	if ((!**s) || o->type != OT_SPHERE)
		return ;
	ft_tmp_sp_truncate_str(*s, 0);
	o -> checkered = !ft_strcmp(*s, "1");
	ft_tmp_sp_truncate_str(*s, 1);
	ft_skip_word_space(s, 0);
}

t_sphere	*ft_sphere(t_tuple pt, double d)
{
	t_sphere	*sp;

	sp = (t_sphere *)ft_calloc(1, sizeof(t_sphere));
	if (!sp)
		return (NULL);
	sp -> pt = pt;
	sp -> d = d;
	return (sp);
}

bool	ft_get_sp(char *s, t_world_tst *w)
{
	t_sphere	sp;
	t_obj		tmp_o;
	t_obj		*o;
	t_material	m;

	ft_bzero(&tmp_o, sizeof(t_obj));
	tmp_o.type = OT_SPHERE;
	s += 2;
	ft_skip_spaces(&s);
	ft_get_tuple(&s, &sp.pt, true);
	ft_skip_spaces(&s);
	ft_get_double(&s, &sp.d);
	ft_skip_spaces(&s);
	m = ft_material();
	// CHECK THE COLOR THING HERE
	ft_get_color(&s, &m.color);
	printf("The str after get color is: >>%s<<\n", s);
	ft_skip_spaces(&s);
	if (*s)
		ft_get_optional_obj_params(&s, &tmp_o);
	if (*s)
		return (false);
	o = ft_objnew(m, tmp_o.checkered, tmp_o.tex, tmp_o.btex);
	if (!o)
		return (false);
	o -> props = ft_sphere(sp.pt, sp.d);
	if (!(o -> props))
		return (false);
	ft_objadd_back(&w->obj_lst, o);
	return (true);
}

bool	ft_extract_el(char *s, t_world_tst *w)
{
	if (ft_get_el_type(s) == EL_TYPE_C)
		return (ft_get_camera(s, w));
	if (ft_get_el_type(s) == EL_TYPE_L)
		return (ft_get_light(s, w));
	if (ft_get_el_type(s) == EL_TYPE_SP)
		return (ft_get_sp(s, w));
	return (true);
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

void	ft_print_light(t_light light)
{
	printf("The light is:\n");
	ft_print_tuple(light.position);
	ft_print_color(light.color);
}

void	ft_print_obj(t_obj *obj)
{
	printf("the type is: %d\n", obj->type);
	printf("the color is: ");
	ft_print_color(obj->material.color);
	printf("checkered is: %d\n", obj->checkered);
	printf("The tex is: ");
	if (obj->tex.pixels)
		ft_print_color(**obj->tex.pixels);
	printf("The btex is: ");
	if (obj->btex.pixels)
	ft_print_color(**obj->btex.pixels);
}

void	ft_parse_rt_file(char *filename)
{
	int			fd;
	t_world_tst		world;
	char		*line;

	// char	*str_types[] = {
	// 		"Camera",
	// 		"Light",
	// 		"Sphere",
	// 		"Plane",
	// 		"Cylinder",
	// 		"Cone",
	// 		"Error"
	// 	};

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		(printf("Error opening the file"), exit(-42));
	
	
	
	line = ft_nullify_nl(get_next_line(fd));
	while (line)
	{
		if (!ft_extract_el(line, &world))
			(printf("ERROR IN FILE FORMAT\n"), exit(-42));
		line = ft_nullify_nl(get_next_line(fd));
	}
	printf("The world light is:\n");
	if (world.light_lst)
		ft_print_light(*(world.light_lst));
	printf("world.obj_lst is: %p\n", world.obj_lst);
	if (world.obj_lst)
		ft_print_obj(world.obj_lst);
	// if (!line/*  && (!world.camera.set) */)
	// 	(printf("You should provide a camera\n"), exit(-42));
	// return ((t_world_tst){(t_ambient){0,g_black}, ft_camera(camera)});
}