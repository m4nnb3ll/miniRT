/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refract.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelayad <abelayad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 12:29:49 by abelayad          #+#    #+#             */
/*   Updated: 2023/12/04 12:32:44 by abelayad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_xnode	*ft_sort_xs(t_xnode *head)
{
	t_xnode	swap;
	t_xnode	*tmp;

	if (!head)
		return (head);
	tmp = head;
	while (tmp && tmp -> next)
	{
		if (tmp->next->x < tmp->x)
		{
			swap = *tmp;
			tmp->x = tmp->next->x;
			tmp->o = tmp->next->o;
			tmp->next->x = swap.x;
			tmp->next->o = swap.o;
			tmp = head;
			continue ;
		}
		tmp = tmp -> next;
	}
	return (head);
}

void	ft_clear_containers(t_contnode	**contlst)
{
	t_contnode	*tmp;
	t_contnode	*next;

	if (!contlst || !*contlst)
		return ;
	tmp = *contlst;
	while (tmp)
	{
		next = tmp -> next;
		free(tmp);
		tmp = next;
	}
	*contlst = NULL;
}

void	ft_get_ns(t_xnode *hit, t_xnode *xs, t_comps *comps)
{
	t_contnode	*contlst;

	contlst = NULL;
	while (xs)
	{
		if (xs == hit)
		{
			if (!contlst)
				comps->ns[0] = VACUUM;
			else
				comps->ns[0] = ft_containers_last(contlst)->o->material.ri;
		}
		if (ft_containers_contain(contlst, xs->o))
			ft_remove_container(&contlst, xs->o);
		else
			ft_contadd_back(&contlst, ft_contnew(xs->o));
		if (xs == hit)
		{
			if (!contlst)
				comps->ns[1] = VACUUM;
			else
				comps->ns[1] = ft_containers_last(contlst)->o->material.ri;
			break ;
		}
		xs = xs -> next;
	}
	ft_clear_containers(&contlst);
}

t_color	ft_refracted_color(t_world *w, t_comps comps, int remaining)
{
	double	n_ratio;
	double	cos_it[2];
	double	sin_t_2;
	t_tuple	direction;
	t_ray	refract_ray;

	if (remaining <= 0 || !comps.o->material.transparency)
		return (g_black);
	n_ratio = comps.ns[0] / comps.ns[1];
	cos_it[0] = ft_dot(comps.ev, comps.nv);
	sin_t_2 = pow(n_ratio, 2) * (1 - pow(cos_it[0], 2));
	if (sin_t_2 > 1)
		return (g_black);
	cos_it[1] = sqrt(1 - sin_t_2);
	direction = ft_sub_tuples(
			ft_sclv(comps.nv, n_ratio * cos_it[0] - cos_it[1]),
			ft_sclv(comps.ev, n_ratio));
	refract_ray = ft_ray(comps.under_pt, direction);
	return (ft_color_scl(ft_color_at(w, refract_ray, remaining - 1),
			comps.o->material.transparency));
}
