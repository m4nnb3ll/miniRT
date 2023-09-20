/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelayad <abelayad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 12:52:34 by abelayad          #+#    #+#             */
/*   Updated: 2023/09/20 12:53:46 by abelayad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void handle_keys(mlx_key_data_t keydata, void* param)
{
	(void)param;
	if (keydata.key == 256)
		exit (0);
}

void	close_window(void *param)
{
	(void)param;
	printf("Window closed\n");
    exit(0);
}

void set_background(mlx_image_t	*image, int width, int height)
{
	int x;
	int	y;

	x = 0;
	while (x < width)
	{
		y = 0;
		while(y < height)
		{
			mlx_put_pixel(image, x, y, 0X3399FF);
			y++;
		}
		x++;
	}
}

t_window	ft_img_ptr(void)
{
	mlx_image_t	*image;
	mlx_t		*mlx;

	mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "miniRT", false);
	image = mlx_new_image(mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	mlx_close_hook(mlx, close_window, NULL);
	mlx_key_hook(mlx, handle_keys, NULL);
	return ((t_window){mlx, image});
}
