#include "minirt.h"

t_color	g_black = (t_color){ 0, 0, 0 };
t_color	g_white = (t_color){ 1, 1, 1 };
t_color	g_red = (t_color){ 1, 0, 0 };
t_color	g_green = (t_color){ 0, 1, 0 };
t_color	g_blue = (t_color){ 0, 0, 1 };

void	ft_print_color(t_color c)
{
	printf("%f %f %f\n", c.r, c.g, c.b);
}

t_color	ft_color(double r, double g, double b)
{
	return ((t_color){ r, g, b });
}

t_color	ft_add_colors(t_color a, t_color b)
{
	return ((t_color){
		a.r + b.r,
		a.g + b.g,
		a.b + b.b
	});
}

t_color	ft_sub_colors(t_color a, t_color b)
{
	return ((t_color){
		a.r - b.r,
		a.g - b.g,
		a.b - b.b
	});
}

t_color	ft_color_scl(t_color c, double scaler)
{
	return ((t_color){
		c.r * scaler,
		c.g * scaler,
		c.b * scaler
	});
}

t_color	ft_multi_colors(t_color a, t_color b)
{
	return ((t_color){
		a.r * b.r,
		a.g * b.g,
		a.b * b.b
	});
}

uint8_t	ft_255channel(double c)
{
	if (c < 0.0)
		return (0);
	if (c > 1.0)
		return (255);
	return (round(c * 255));
}
