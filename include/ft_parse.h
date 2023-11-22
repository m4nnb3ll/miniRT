/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelayad <abelayad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 15:44:36 by abelayad          #+#    #+#             */
/*   Updated: 2023/11/15 22:07:11 by abelayad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PARSE_H
# define FT_PARSE_H

# include "minirt_types.h"

enum e_el_type	ft_get_el_type(char *s);
t_world			ft_parse_rt_file(char *filename);

// UTILS GO BELOW

int		ft_strcmp(const char *s1, const char *s2);
void	ft_skip_spaces(char **s);
bool	ft_tuple_check(char *s);
bool	ft_color_check(char *s);
int		ft_get_strs_count(char **strs);
void	ft_tmp_sp_truncate_str(char *s, bool reverse);
bool	ft_get_color_channel_converted(double *channel, char *chan_str);
void	ft_skip_token(char **s);
void	ft_skip_token_space(char **s, bool space_first);

#endif