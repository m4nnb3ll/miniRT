/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   containers.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelayad <abelayad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 15:15:26 by abelayad          #+#    #+#             */
/*   Updated: 2023/09/28 15:12:17 by abelayad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_contnode	*ft_contnew(t_objnode *o)
{
	t_contnode	*new;

	new = ft_calloc(1, sizeof(t_contnode));
	if (!new)
		return (NULL);
	new -> o = o;
	return (new);
}

void	ft_contadd_back(t_contnode **contlst, t_contnode *n)
{
	t_contnode	*tmp;

	if (!contlst || !n)
		return ;
	if (!*contlst)
		*contlst = n;
	else
	{
		tmp = *contlst;
		while (tmp -> next)
			tmp = tmp -> next;
		tmp -> next = n;
	}
}

bool	ft_containers_contain(t_contnode *contlst, t_objnode *o)
{
	while (contlst)
	{
		if (contlst->o == o)
			return (true);
		contlst = contlst -> next;
	}
	return (false);
}

t_contnode	*ft_containers_last(t_contnode *contlst)
{
	while (contlst)
	{
		if (!contlst -> next)
			return (contlst);
		contlst = contlst -> next;
	}
	return (contlst);
}

void	ft_remove_container(t_contnode **head, t_objnode *o)
{
	t_contnode	*prev;
	t_contnode	*tmp;

	if (!head || !*head || !o)
		return ;
	prev = *head;
	if ((*head)->o == o)
	{
		*head = prev -> next;
		free(prev);
		return ;
	}
	tmp = *head;
	while (tmp)
	{
		if (tmp->o == o)
		{
			prev -> next = tmp->next;
			free(tmp);
			tmp = prev -> next;
		}
		else
		{
			prev = tmp;
			tmp = tmp -> next;
		}
	}
}