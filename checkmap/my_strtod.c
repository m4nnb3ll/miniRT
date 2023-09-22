/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_strtod.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogorfti <ogorfti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 15:41:33 by ogorfti           #+#    #+#             */
/*   Updated: 2023/09/22 17:28:02 by ogorfti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	valid_input(char *str)
{
	int	dot;
	int	i;

	i = 0;
	dot = 0;
	while (str[i])
	{
		if ((!ft_isdigit(str[i]) && str[i] != '.'
				&& str[i] != '-') || (i == 0 && str[i] == '.'))
			error_msg("Error: invalid input!\n");
		if (str[i] == '.')
			dot++;
		i++;
	}
	if (dot > 1 || (i > 0 && str[i - 1] == '.'))
		error_msg("Error: invalid input!\n");
}

int	ft_sign(char **str, double *res)
{
	int	sign;

	sign = 1;
	valid_input(*str);
	if (**str == '-')
	{
		sign = -1;
		(*str)++;
	}
	else if (**str == '+')
		(*str)++;
	*res = 0.0;
	return (sign);
}

double	my_strtod(char *str)
{
	double		div;
	double		dec;
	double		res;
	int			sign;

	sign = ft_sign(&str, &res);
	while (ft_isdigit(*str))
	{
		res = res * 10.0 + (*str - '0');
		str++;
	}
	if (*str == '.')
	{
		str++;
		dec = 0.0;
		div = 10.0;
		while (ft_isdigit(*str))
		{
			dec += (*str - '0') / div;
			div *= 10.0;
			str++;
		}
		res += dec;
	}
	return (sign * res);
}
