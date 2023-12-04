/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelayad <abelayad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 16:09:43 by abelayad          #+#    #+#             */
/*   Updated: 2023/12/04 12:34:18 by abelayad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	*ft_render_wrapper(void *arg)
{
	t_chunk	*chunk;

	chunk = arg;
	ft_render(chunk->img, chunk->w, chunk->num);
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_world		w;
	t_png_img	img;
	t_chunk		*chunks;

	if (argc != 2)
		return (printf("Please provide a scene file!\n"), -42);
	img = ft_allocate_png_img(SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!img.row_pointers)
		return (printf("Error allocating the image\n"), -42);
	w = ft_parse_rt_file(argv[1]);
	chunks = ft_calloc(w.cores_cnt, sizeof(t_chunk));
	if (!chunks)
		return (42);
	for (int i=0; i < w.cores_cnt; i++)
	{
		chunks[i].img = &img;
		chunks[i].w = &w;
		chunks[i].num = i;
	}
	for (int i=0; i < w.cores_cnt; i++)
		if (pthread_create(&chunks[i].thread, NULL, ft_render_wrapper, &chunks[i]) != 0)
			(perror("pthread_create"), exit(2));
	for (int i=0; i < w.cores_cnt; i++)
		pthread_join(chunks[i].thread, NULL);
	free_world(&w);
	ft_write_png_file("scene.png", img);
	free(chunks);
}
