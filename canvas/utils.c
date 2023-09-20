/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelayad <abelayad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 12:52:32 by abelayad          #+#    #+#             */
/*   Updated: 2023/09/20 12:52:32 by abelayad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

uint8_t	ft_255channel(double c)
{
	if (c < 0.0)
		return (0);
	if (c > 1.0)
		return (255);
	return (round(c * 255));
}