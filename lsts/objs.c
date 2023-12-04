/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelayad <abelayad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 15:15:26 by abelayad          #+#    #+#             */
/*   Updated: 2023/10/27 20:30:07 by abelayad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_obj	*ft_objnew(enum e_obj_type ot)
{
	t_obj	*new;

	new = ft_calloc(1, sizeof(t_obj));
	if (!new)
		return (NULL);
	new -> type = ot;
	new -> material = ft_material();
	return (new);
}

void	ft_objadd_back(t_obj **objlst, t_obj *n)
{
	t_obj	*tmp;

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
