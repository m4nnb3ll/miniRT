#ifndef TUPLES_H
# define TUPLES_H

#include "minirt_types.h"

void		ft_print_tuple(t_tuple a);
t_tuple	ft_point(double x, double y, double z);
t_tuple	ft_vector(double x, double y, double z);
t_tuple	ft_add_tuples(t_tuple a, t_tuple b);
t_tuple	ft_sub_tuples(t_tuple a, t_tuple b);
t_tuple	ft_negv(t_tuple a);
t_tuple	ft_sclv(t_tuple a, double sclr);
double	ft_mag(t_tuple v);
double	ft_dot(t_tuple a, t_tuple b);
t_tuple	ft_cross(t_tuple a, t_tuple b);
double	ft_mag(t_tuple v);
t_tuple	ft_normalize(t_tuple v);

#endif