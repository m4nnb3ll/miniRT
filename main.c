#include "minirt.h"

int main()
{
	t_canvas	c;

	for (int i=0; i < CANVAS_HEIGHT; i++)
	{
		for (int j=0; j < CANVAS_WIDTH; j++)
			ft_write_pixel(&c, i, j, ft_color(1, 1, 0));
	}
	ft_canvas_to_ppm(c);
}