/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelayad <abelayad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 15:15:26 by abelayad          #+#    #+#             */
/*   Updated: 2023/09/28 12:41:44 by abelayad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_objnode	*ft_objnew(void)
{
	t_objnode	*new;

	new = ft_calloc(1, sizeof(t_objnode));
	if (!new)
		return (NULL);
	return (new);
}

void	ft_objadd_back(t_objnode **objlst, t_objnode *n)
{
	t_objnode	*tmp;

	if (!objlst || !n)
		return ;
	if (!*objlst)
		*objlst = n;
	else
	{
		tmp = *objlst;
		while (tmp -> next)
			tmp = tmp -> next;
		tmp -> next = n;
	}
}
