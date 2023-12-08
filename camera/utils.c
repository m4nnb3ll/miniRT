/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelayad <abelayad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 15:45:07 by abelayad          #+#    #+#             */
/*   Updated: 2023/12/08 10:34:45 by abelayad         ###   ########.fr       */
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

void	ft_print_progress(t_world *w)
{
	int		i;
	int		step;
	double	progress;

	step = SCREEN_HEIGHT / 10;
	pthread_mutex_lock(&w->progress_mtx);
	if (!step || !(w->lines_progress % step))
	{
		progress = (w->lines_progress / (double)SCREEN_HEIGHT) * 20;
		printf("\rrendering: %s[", WHITE);
		i = -1;
		while (++i < (int)progress)
			printf("=");
		printf(">] %s%%%3d%s",
			GREEN, (int)round(progress / 20 * 100), RESET_COLOR);
		if (w->lines_progress > SCREEN_HEIGHT - step)
			printf("\n%sCompleted!%s\n", GREEN, RESET_COLOR);
		else
			fflush(stdout);
	}
	pthread_mutex_unlock(&w->progress_mtx);
}
