#ifndef FT_PRINTERS_H
# define FT_PRINTERS_H

# include "minirt_types.h"

void	ft_print_matrix(t_matrix m);
void	ft_print_camera(t_camera c);
void	ft_print_light(t_light *light);
void	ft_print_obj(t_obj *obj);
void	ft_print_lights(t_light *light_lst);
void	ft_print_objs(t_obj *obj_lst);
void	ft_print_tuple(t_tuple t);
void	ft_print_color(t_color c);

#endif