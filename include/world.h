/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogorfti <ogorfti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 12:27:14 by ogorfti           #+#    #+#             */
/*   Updated: 2023/09/21 11:29:11 by ogorfti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WORLD_H
# define WORLD_H

double		my_strtod(char *str);
int			nbr_info(char **str);
int			ft_strcmp(char *s1, char *s2);
int			check_range(t_tuple tuple);
double		translatecolor(double color);
void		error_msg(char *str);
void		allocate_map(char *file, t_data *data);
void		split_data(t_data *data);
void		free_double(char **ptr);
void		free_struct(t_find *find);
int			check_name(char *str);
int			calculate_objs(t_data *data);
void		check_count(t_data *data);
void		world_data(t_world *world, char *filename);
void		ambient_data(char **split, t_ambient *ambient);
void		camera_data(char **split, t_camera *camera);
void		light_data(char **split, t_light *light);
void		cylinder_data(char **split, t_obj *obj);
void		sphere_data(char **split, t_obj *obj);
void		plane_data(char **split, t_obj *obj);
void		cone_data(char **split, t_obj *obj);
void		readppm(char *file, t_btex *ppm);
void		ppm_data(t_btex *ppm);

#endif