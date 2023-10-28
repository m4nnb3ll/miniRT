/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelayad <abelayad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 15:15:26 by abelayad          #+#    #+#             */
/*   Updated: 2023/09/26 17:26:52 by abelayad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_light	*ft_lightnew(t_tuple position, t_color color)
{
	t_light	*new;

	new = ft_calloc(1, sizeof(t_light));
	if (!new)
		return (NULL);
	new -> position = position;
	new -> color = color;
	return (new);
}

void	ft_lightadd_back(t_light **lightlst, t_light *n)
{
	t_light	*tmp;

	if (!lightlst || !n)
		return ;
	if (!*lightlst)
		*lightlst = n;
	else
	{
		tmp = *lightlst;
		while (tmp -> next)
			tmp = tmp -> next;
		tmp -> next = n;
	}
}
