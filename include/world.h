/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelayad <abelayad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 12:27:14 by ogorfti           #+#    #+#             */
/*   Updated: 2023/09/20 13:59:46 by abelayad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WORLD_H
# define WORLD_H

char	**split_string(char *s);
double	my_strtod(char *str);
int		nbr_info(char **str);
int		ft_strcmp(char *s1, char *s2);
int		check_range(t_tuple tuple);
double	translatecolor(double color);
void	error_msg(char *str);
void	allocate_map(char *file, t_data *data);
void	split_data(t_data *data);
void	free_double(char **ptr);
void	free_struct(t_find *find);
int		calculate_objs(t_data *data);
int		check_name(char *str);
void	world_data(t_world *world, char *filename);
void	display_map(char **map);
void	readppm(char *file, t_btex *ppm);
void	ppm_data(t_btex *ppm);

#endif