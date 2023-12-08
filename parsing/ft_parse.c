/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelayad <abelayad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 15:42:20 by abelayad          #+#    #+#             */
/*   Updated: 2023/12/08 10:19:25 by abelayad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	ft_get_color(char **s, t_color *c)
{
	char	**tuple_split;

	ft_skip_spaces(s);
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
	ft_skip_token_space(s, 0);
	return (true);
}

// ft_skip_token(&s); skips the type name
bool	ft_get_camera(char *s, t_world *w)
{
	ft_skip_token(&s);
	if (!ft_get_tuple(&s, &w->camera.from, true)
		|| !ft_get_tuple(&s, &w->camera.to, true)
		|| !ft_get_double(&s, &w->camera.fov)
		|| w->camera.fov < 0 || w->camera.fov > 180)
		return (false);
	w->camera.set = true;
	return (!*s);
}

// ft_skip_token(&s); skips the type name
bool	ft_get_light(char *s, t_world *w)
{
	t_light	tmp_light;
	t_light	*light;

	ft_skip_token(&s);
	if (!ft_get_tuple(&s, &tmp_light.position, true)
		|| !ft_get_color(&s, &tmp_light.color))
		return (false);
	if (*s)
		return (false);
	light = ft_lightnew(tmp_light.position, tmp_light.color);
	if (!light)
		return (false);
	return (ft_lightadd_back(&w->light_lst, light), true);
}

// if (!**s) return (true); // if there is no more options, return
bool	ft_get_optional_obj_params(char **s, t_obj *o)
{
	ft_skip_spaces(s);
	ft_tmp_sp_truncate_str(*s, 0);
	o -> checkered = !ft_strcmp(*s, "1");
	ft_tmp_sp_truncate_str(*s, 1);
	ft_skip_token_space(s, 0);
	if (!**s)
		return (true);
	ft_tmp_sp_truncate_str(*s, 0);
	if (ft_strcmp(*s, ".") != 0)
		o -> tex = ft_png_img_to_tex(ft_read_png_file(*s));
	ft_tmp_sp_truncate_str(*s, 1);
	ft_skip_token_space(s, 0);
	if (!**s)
		return (true);
	if (o->type != OT_SPHERE && o->type != OT_PLANE)
		return (false);
	ft_tmp_sp_truncate_str(*s, 0);
	if (ft_strcmp(*s, ".") != 0)
		o -> btex = ft_png_img_to_tex(ft_read_png_file(*s));
	ft_tmp_sp_truncate_str(*s, 1);
	ft_skip_token_space(s, 0);
	return (!**s);
}

t_world	ft_parse_rt_file(char *filename)
{
	int			fd;
	t_world		world;
	char		*line;

	ft_bzero(&world, sizeof(t_world));
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		(printf("Error opening the file"), exit(42));
	line = ft_nullify_nl(get_next_line(fd));
	while (line)
	{
		if (*line && *line != '#' && !ft_extract_el(line, &world))
			exit(ft_print_parse_err(line));
		free(line);
		line = ft_nullify_nl(get_next_line(fd));
	}
	if (!world.camera.set || !world.light_lst)
		exit(printf("%sCamera or Light is missing!!!%s\n", RED, RESET_COLOR));
	world.camera = ft_camera(world.camera);
	world.cores_cnt = sysconf(_SC_NPROCESSORS_ONLN) * 3;
	pthread_mutex_init(&world.progress_mtx, NULL);
	return (world);
}
