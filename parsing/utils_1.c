/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelayad <abelayad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 17:13:39 by abelayad          #+#    #+#             */
/*   Updated: 2023/12/03 19:45:06 by abelayad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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

// Check for s before passing it to this function
enum e_el_type	ft_get_el_type(char *s)
{
	if (s[0] == 'C' && s[1] == ' ')
		return (EL_TYPE_C);
	if (s[0] == 'l' && s[1] == ' ')
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

bool	ft_get_tuple(char **s, t_tuple *t, bool is_pt)
{
	char	**tuple_split;

	ft_skip_spaces(s);
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
	ft_skip_token(s);
	return (true);
}

bool	ft_get_double(char **s, double *val)
{
	char	*start;

	ft_skip_spaces(s);
	if (!ft_strlen(*s))
		return (false);
	ft_tmp_sp_truncate_str(*s, 0);
	start = *s;
	while (**s && (ft_isdigit(**s) || **s == '.'))
		(*s)++;
	if (**s)
		return (false);
	*val = atof(start);
	ft_tmp_sp_truncate_str(*s, 1);
	return (true);
}

bool	ft_extract_el(char *s, t_world *w)
{
	enum e_el_type	type;

	type = ft_get_el_type(s);
	if (type == EL_TYPE_C)
		return (ft_get_camera(s, w));
	else if (type == EL_TYPE_L)
		return (ft_get_light(s, w));
	else if (type == EL_TYPE_SP)
		return (ft_get_sp(s, w));
	else if (type == EL_TYPE_PL)
		return (ft_get_pl(s, w));
	else if (type == EL_TYPE_CY || type == EL_TYPE_CN)
	{
		if (type == EL_TYPE_CY)
			return (ft_get_cycone(s, w, OT_CYLINDER));
		return (ft_get_cycone(s, w, OT_CONE));
	}
	return (false);
}
