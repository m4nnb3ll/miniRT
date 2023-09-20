/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fequals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelayad <abelayad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 14:00:21 by abelayad          #+#    #+#             */
/*   Updated: 2023/09/20 15:00:57 by abelayad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#define EPSILON 0.00001

bool	ft_fequals(double a, double b)
{
	if (fabs(a - b) < EPSILON)
		return (true);
	return (false);
}
