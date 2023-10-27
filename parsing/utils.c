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
	while (ft_isalnum(**s) || **s == '.' || **s == '_' || **s == ',' || **s == '-')
		(*s)++;
}

void	ft_skip_token_space(char **s, bool space_first)
{
	if (space_first)
		(ft_skip_spaces(s), ft_skip_token(s));
	else
		(ft_skip_token(s), ft_skip_spaces(s));
}