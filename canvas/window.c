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
	int x = 0,y = 0;

	// printf("The image ptr from inside is: %p\n", image);
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
	// printf("The image produced: %p\n", image);
	// set_background(image, SCREEN_WIDTH, SCREEN_HEIGHT);
	//handle red cross and ESC in subject
	mlx_close_hook(mlx, close_window, NULL);
	mlx_key_hook(mlx, handle_keys, NULL);
	return ((t_window){mlx, image});
}

// int main()
// {
// 	mlx_image_t	*image = image_ptr();
// }
