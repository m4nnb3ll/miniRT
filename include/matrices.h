#ifndef MATRICES_H
# define MATRICES_H

#include "minirt_types.h"

void			ft_print_matrix(t_matrix m);
t_matrix	ft_submatrix(t_matrix m, int row, int col);
double		ft_determinant(t_matrix m);
t_matrix	ft_transpose(t_matrix m);
t_matrix	ft_cofactor_matrix(t_matrix m);
t_matrix	ft_inverse(t_matrix original);
t_matrix	ft_multi_matrices(t_matrix a, t_matrix b);

#endif