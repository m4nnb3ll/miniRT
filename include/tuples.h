#ifndef TUPLES_H
# define TUPLES_H

#include "minirt_types.h"

void		ft_print_tuple(t_tuple a);
t_tuple	ft_point(double x, double y, double z);
t_tuple	ft_vector(double x, double y, double z);
t_tuple	ft_add_tuples(t_tuple a, t_tuple b);
t_tuple	ft_sub_tuples(t_tuple a, t_tuple b);
t_tuple	ft_neg_vec(t_tuple a);
t_tuple	ft_scl_vec(t_tuple a, double sclr);

#endif