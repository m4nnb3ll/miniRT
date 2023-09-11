#ifndef	CANVAS_H
#define	CANVAS_H

# include "minirt_types.h"

void			ft_print_canvas(t_canvas canvas);
void			ft_write_pixel(t_canvas *c, uint32_t row, uint32_t col, t_color color);
void			ft_canvas_to_ppm(t_canvas *canvas);
void			ft_print_color(t_color c);
t_color		ft_color(double r, double g, double b);
t_color		ft_add_colors(t_color a, t_color b);
t_color		ft_sub_colors(t_color a, t_color b);
t_color		ft_color_scl(t_color c, double scaler);
t_color		ft_multi_colors(t_color a, t_color b);
uint8_t		ft_255channel(double c);

#endif