/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_strtod.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogorfti <ogorfti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 15:41:33 by ogorfti           #+#    #+#             */
/*   Updated: 2023/09/20 15:56:30 by ogorfti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	ft_sign(char **str, double *res)
{
	int	sign;

	sign = 1;
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
