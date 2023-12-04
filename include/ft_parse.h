/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelayad <abelayad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 15:44:36 by abelayad          #+#    #+#             */
/*   Updated: 2023/12/04 12:34:25 by abelayad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PARSE_H
# define FT_PARSE_H

# include "minirt_types.h"

enum e_el_type	ft_get_el_type(char *s);
t_world			ft_parse_rt_file(char *filename);
int				ft_strcmp(const char *s1, const char *s2);
void			ft_skip_spaces(char **s);
bool			ft_tuple_check(char *s);
bool			ft_color_check(char *s);
int				ft_get_strs_count(char **strs);
void			ft_tmp_sp_truncate_str(char *s, bool reverse);
bool			ft_get_color_channel_converted(double *channel, char *chan_str);
void			ft_skip_token(char **s);
void			ft_skip_token_space(char **s, bool space_first);
bool			ft_get_sp(char *s, t_world *w);
bool			ft_get_pl(char *s, t_world *w);
bool			ft_get_cycone(char *s, t_world *w, enum e_obj_type type);
bool			ft_get_color(char **s, t_color *c);
bool			ft_get_camera(char *s, t_world *w);
bool			ft_get_light(char *s, t_world *w);
bool			ft_get_optional_obj_params(char **s, t_obj *o);
char			*ft_nullify_nl(char *s);
bool			ft_get_tuple(char **s, t_tuple *t, bool is_pt);
bool			ft_get_double(char **s, double *val);
bool			ft_extract_el(char *s, t_world *w);
int				ft_print_parse_err(char *str);

#endif