/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelayad <abelayad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 15:45:07 by abelayad          #+#    #+#             */
/*   Updated: 2023/12/03 22:23:30 by abelayad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	ft_free_lights(t_light *light_lst)
{
	t_light	*to_free;

	while (light_lst)
	{
		to_free = light_lst;
		light_lst = light_lst->next;
		free(to_free);
	}
}

void	free_world(t_world *w)
{
	t_obj	*tmp_o;
	t_obj	*obj_to_free;

	tmp_o = w->obj_lst;
	while (tmp_o)
	{
		ft_free_tex(tmp_o->tex);
		ft_free_tex(tmp_o->btex);
		obj_to_free = tmp_o;
		tmp_o = tmp_o -> next;
		free(obj_to_free);
	}
	ft_free_lights(w->light_lst);
}
