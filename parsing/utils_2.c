/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelayad <abelayad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 19:03:55 by abelayad          #+#    #+#             */
/*   Updated: 2023/12/04 16:57:25 by abelayad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
	*channel = atoi(chan_str) / 255.0;
	return (*channel >= 0 && *channel <= 1);
}

void	ft_skip_token(char **s)
{
	while (ft_isalnum(**s) || **s == '.' || **s == '_'
		|| **s == ',' || **s == '-' || **s == '/')
		(*s)++;
}

void	ft_skip_token_space(char **s, bool space_first)
{
	if (space_first)
		(ft_skip_spaces(s), ft_skip_token(s));
	else
		(ft_skip_token(s), ft_skip_spaces(s));
}

int	ft_print_parse_err(char *str)
{
	printf("ERROR IN FILE FORMAT: %s`%s`%s\n", RED, str, RESET_COLOR);
	printf("Please read %s`scenes/sample.rt`%s for further detail.\n",
		YELLOW, RESET_COLOR);
	return (1);
}
