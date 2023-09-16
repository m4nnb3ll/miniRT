#ifndef MATRICES_H
# define MATRICES_H

#include "minirt_types.h"

void			ft_print_matrix(t_matrix m);
t_matrix	ft_submatrix(t_matrix m, int row, int col);
double		ft_determinant(t_matrix m);
t_matrix	ft_transpose(t_matrix m);
t_matrix	ft_cofactor_matrix(t_matrix m);
t_matrix	ft_inverse(t_matrix original);
t_matrix	ft_matrix_scl(t_matrix a, double scl);
t_matrix	ft_multi_matrices(t_matrix a, t_matrix b);
t_matrix	ft_translate(double x, double y, double z);
t_matrix	ft_scale(double x, double y, double z);
t_matrix	ft_rotate_x(double rad);
t_matrix	ft_rotate_y(double rad);
t_matrix	ft_rotate_z(double rad);
t_tuple		ft_transform_tuple(t_matrix m, t_tuple t);
t_tuple		ft_get_quat(t_tuple rot_axe, double radian);
t_matrix	ft_quat_to_matrix(t_tuple q);
t_matrix	ft_get_rotation_matrix(t_tuple v1, t_tuple v2);

#endif