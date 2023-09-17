/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogorfti <ogorfti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 12:27:14 by ogorfti           #+#    #+#             */
/*   Updated: 2023/09/16 11:59:49 by ogorfti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WORD_H
#define	WORD_H

char		**split_string(char *s);
double		my_strtod(char *str);

int			nbr_info(char **str, int shouldbe);
int			ft_strcmp(char *s1, char *s2);
int			check_range(t_tuple tuple);
double		translatecolor(double color);
void		error_msg(char *str);

void		allocate_map(char *file, t_data *data);
void		split_data(t_data *data);
void		free_double(char **ptr);
void	    free_struct(t_find *find);
int			calculate_objs(t_data *data);
int         check_name(char *str);
void        world_data(t_world *world, char *filename);

//TMP
void	    display_map(char **map);
//TMP

#endif