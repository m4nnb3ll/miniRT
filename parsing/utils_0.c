/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_0.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelayad <abelayad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 19:03:49 by abelayad          #+#    #+#             */
/*   Updated: 2023/12/03 19:03:50 by abelayad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	s1_len;
	size_t	s2_len;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	if (s1_len > s2_len)
		return (ft_strncmp(s1, s2, s1_len));
	else
		return (ft_strncmp(s1, s2, s2_len));
}

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
