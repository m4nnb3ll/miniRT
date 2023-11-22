/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelayad <abelayad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 15:45:07 by abelayad          #+#    #+#             */
/*   Updated: 2023/11/22 22:45:39 by abelayad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

uint32_t	ft_merge_colors(int r, int g, int b, int a)
{
	if (ENDIANESS == 0)
		return (a << 24 | b << 16 | g << 8 | r);
	return (r << 24 | g << 16 | b << 8 | a);
}

void	ft_free_lights(t_light *light_lst)
{
	t_light	*to_free;

	while (light_lst)
	{
		to_free = light_lst;
		light_lst = light_lst->next;
		free(to_free);
		printf("forever\n");
	}
}

// rename it to free_world
void	ft_free_objs_and_tex(t_world *w)
{
	t_obj	*tmp_o;
	t_obj	*obj_to_free;
// ft_free_xs

	tmp_o = w->obj_lst;
	while (tmp_o)
	{
		ft_free_tex(tmp_o->tex);
		ft_free_tex(tmp_o->btex);
		obj_to_free = tmp_o;
		tmp_o = tmp_o -> next;
		free(obj_to_free);
		printf("forever2\n");
	}
	ft_free_lights(w->light_lst);
}
