/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelayad <abelayad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 15:45:07 by abelayad          #+#    #+#             */
/*   Updated: 2023/10/27 20:29:35 by abelayad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

uint32_t	ft_merge_colors(int r, int g, int b, int a)
{
	if (ENDIANESS == 0)
		return (a << 24 | b << 16 | g << 8 | r);
	return (r << 24 | g << 16 | b << 8 | a);
}

void	ft_free_objs_and_tex(t_world *w)
{
	(void)w;
	// int	i;

	// i = 0;
	// while (i < w->num_objs)
	// {
	// 	ft_free_tex(w->objs[i].tex);
	// 	free(w->objs[i].props);
	// 	i++;
	// }
	// free(w->objs);
}
