#include "minirt.h"

void handle_keys(mlx_key_data_t keydata, void* param)
{
	// printf("%d\n", keydata.key);
	exit (0);
}

void	close_window(void *param)
{
	printf("Window closed\n");
    exit(0);
}

void set_background(mlx_image_t	*image, int width, int height)
{
	int x = 0,y = 0;

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

mlx_image_t *image_ptr(void)
{
	mlx_image_t	*image;
	mlx_t		*mlx;

	mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "miniRT", false);
	image = mlx_new_image(mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	
	//tmp func
	set_background(image, SCREEN_WIDTH, SCREEN_HEIGHT);
	
	//display image at the coordinates (0, 0)
	mlx_image_to_window(mlx, image, 0,0);
	
	//handle red cross and ESC in subject
	mlx_close_hook(mlx, close_window, NULL);
	mlx_key_hook(mlx, handle_keys, NULL);
	mlx_loop(mlx);

	return (image);
}

// int main()
// {
// 	mlx_image_t	*image = image_ptr();
// }
