#include "minirt.h"

const t_matrix	g_identity_matrix = {
	4, {
		{1, 0, 0, 0},
		{0, 1, 0, 0},
		{0, 0, 1, 0},
		{0, 0, 0, 1}
	}
};

void	ft_print_matrix(t_matrix m)
{
	int	i, j;

	printf("Matrix size: %d\n", m.size);
	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			printf("%f ", m.val[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}

t_matrix	ft_matrix_scl(t_matrix m, double scl)
{
	int	i, j;

	i = 0;
	while (i < m.size && i < 3)
	{
		j = 0;
		while (j < m.size  && j < 3)
		{
			m.val[i][j] = m.val[i][j] * scl;
			j++;
		}
		i++;
	}
	return (m);
}

t_matrix	ft_multi_matrices(t_matrix a, t_matrix b)
{
	t_matrix	c;
	int				i;
	int				j;

	c = g_identity_matrix;
	i = 0;
	while (i < c.size)
	{
		j = 0;
		while (j < c.size)
		{
			c.val[i][j] = a.val[i][0] * b.val[0][j] + a.val[i][1] * b.val[1][j] +
			a.val[i][2] * b.val[2][j] + a.val[i][3] * b.val[3][j];
			j++;
		}
		i++;
	}
	return	(c);
}

t_matrix	ft_submatrix(t_matrix m, int row, int col)
{
	t_matrix	new_m;
	int				i;
	int				j;
	int				k;
	int				l;

	if (m.size == 1)
		return (m);
	new_m.size = m.size - 1;
	i = 0;
	k = 0;
	while (i < m.size)
	{
		j = 0;
		l = 0;
		while (j < m.size)
		{
			new_m.val[k][l] = m.val[i][j];
			l += (j++ != col);
		}
		k += (i++ != row);
	}
	return (new_m);
}

double	ft_determinant(t_matrix m)
{
	int			sign;
	double	det;
	int			i;

	if (m.size == 2)
		det = m.val[0][0] * m.val[1][1] - m.val[0][1] * m.val[1][0];
	else
	{
		det = 0;
		i = 0;
		while (i < m.size)
		{
			sign = 1 + -2 * (i % 2 != 0);
			det += sign * m.val[0][i] * ft_determinant(ft_submatrix(m, 0, i));
			i++;
		}
	}
	// printf("The determinant is: %f\n", det);
	return (det);
}

t_matrix	ft_transpose(t_matrix m)
{
	int				i;
	int				j;
	t_matrix	new_m;
	
	new_m.size = m.size;
	i = 0;
	while (i < m.size)
	{
		j = 0;
		while (j < m.size)
		{
			new_m.val[i][j] = m.val[j][i];
			j++;
		}
		i++;
	}
	return (new_m);
}

t_matrix	ft_cofactor_matrix(t_matrix m)
{
	int				i;
	int				j;
	int				sign;
	t_matrix	co_matrix;

	co_matrix.size = m.size;
	i = 0;
	while (i < m.size)
	{
		j = 0;
		while (j < m.size)
		{
			sign = 1 + -2 * ((i + j) % 2 != 0);
			co_matrix.val[i][j] = sign * ft_determinant(ft_submatrix(m, i, j));
			j++;
		}
		i++;
	}
	return (co_matrix);
}

t_matrix	ft_inverse(t_matrix original)
{
	int				i;
	int				j;
	t_matrix	inverse;
	double		determinant;

	determinant = ft_determinant(original);
	if (!determinant)
		return (g_identity_matrix);
	inverse = ft_transpose(ft_cofactor_matrix(original));
	i = 0;
	while (i < inverse.size)
	{
		j = 0;
		while (j < inverse.size)
		{
			inverse.val[i][j] = inverse.val[i][j] / determinant;
			j++;
		}
		i++;
	}
	return (inverse);
}
