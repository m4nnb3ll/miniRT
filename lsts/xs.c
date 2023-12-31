/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xs.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelayad <abelayad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 15:15:26 by abelayad          #+#    #+#             */
/*   Updated: 2023/10/27 20:27:53 by abelayad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_xnode	*ft_xnew(t_obj *o, double x)
{
	t_xnode	*new;

	new = ft_calloc(1, sizeof(t_xnode));
	if (!new)
		return (NULL);
	new -> o = o;
	new -> x = x;
	return (new);
}

void	ft_xadd_back(t_xnode **xlst, t_xnode *n)
{
	t_xnode	*tmp;

	if (!xlst || !n)
		return ;
	if (!*xlst)
		*xlst = n;
	else
	{
		tmp = *xlst;
		while (tmp -> next)
			tmp = tmp -> next;
		tmp -> next = n;
	}
}
