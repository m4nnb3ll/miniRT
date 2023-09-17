// gcc window.c  ~/MLX42/build/libmlx42.a -Iinclude -lglfw
//  -L/goinfre/ogorfti/.brew/opt/glfw/lib/ -framework Cocoa -framework OpenGL -framework IOKit
#include "../../../MLX42/include/MLX42/MLX42.h"
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

	mlx = mlx_init(600, 400, "miniRT", false);
	image = mlx_new_image(mlx, 600, 400);
	
	//tmp func
	set_background(image, 600, 400);
	
	//display image at the coordinates (0, 0)
	mlx_image_to_window(mlx, image, 0,0);
	
	//handle red cross and ESC in subject
	mlx_close_hook(mlx, close_window, NULL);
	mlx_key_hook(mlx, handle_keys, NULL);
	mlx_loop(mlx);

	return (image);
}

int main()
{
	mlx_image_t	*image = image_ptr();
}
