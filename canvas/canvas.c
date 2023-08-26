#include "minirt.h"

void	ft_write_pixel(t_canvas *c, uint32_t row, uint32_t col, t_color color)
{
	if (row < CANVAS_HEIGHT && col < CANVAS_WIDTH)
		c->pixel_grid[row][col] = color;
}

void	ft_print_canvas(t_canvas canvas)
{
	for(int i=0; i< CANVAS_HEIGHT; i++)
	{
		for(int j=0; j< CANVAS_WIDTH; j++)
		{
			printf("[%d][%d]: ", i, j);
			ft_print_color(canvas.pixel_grid[i][j]);
		}
	}
}

void	ft_canvas_to_ppm(t_canvas canvas)
{
	uint32_t	x;
	uint32_t	y;
	uint32_t	row_length;
	t_color		color;
	int				file_fd;

	file_fd = open("test.ppm", O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (file_fd == -1)
		(printf("Failed to open file \"test.ppm\"\n"), exit(1));
	if (dup2(file_fd, 1) == -1)
		(printf("dup2 failed \"test.ppm\"\n"), exit(1));
	close(file_fd);
	printf("%s\n", PPM_MAGIC_NUM);
	printf("%d %d\n", CANVAS_WIDTH, CANVAS_HEIGHT);
	printf("%d\n", PPM_MAX_COLOR);
	y = 0;
	row_length = 0;
	while (y < CANVAS_HEIGHT)
	{
		x = 0;
		while (x < CANVAS_WIDTH)
		{
			// RED
			// 5 for space + color-max-length + \n
			if (row_length > 70 - 5)
			{
				printf("\n");
				row_length = 0;
			}
			if (row_length)
			{
				row_length += printf(" ");
			}
			color = canvas.pixel_grid[y][x];
			row_length += printf("%d",
				ft_255channel(color.r));
			
			// GREEN
			// 5 for space + color-max-length + \n
			if (row_length > 70 - 5)
			{
				printf("\n");
				row_length = 0;
			}
			if (row_length)
			{
				row_length += printf(" ");
			}
			row_length += printf("%d",
				ft_255channel(color.g));
			
			// BLUE
			// 5 for space + color-max-length + \n
			if (row_length > 70 - 5)
			{
				printf("\n");
				row_length = 0;
			}
			if (row_length)
			{
				row_length += printf(" ");
			}
			row_length += printf("%d",
				ft_255channel(color.b));
			x++;
		}
		row_length = (printf("\n"), 0);
		y++;
	}
}
