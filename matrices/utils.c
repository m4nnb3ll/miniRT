/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelayad <abelayad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 15:16:27 by abelayad          #+#    #+#             */
/*   Updated: 2023/09/20 15:18:52 by abelayad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_matrix	ft_submatrix(t_matrix m, int row, int col)
{
	t_matrix	new_m;
	int			i;
	int			j;
	int			k;
	int			l;

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
	int		sign;
	double	det;
	int		i;

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
	return (det);
}

t_matrix	ft_cofactor_matrix(t_matrix m)
{
	int			i;
	int			j;
	int			sign;
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

t_tuple	ft_transform_tuple(t_matrix m, t_tuple t)
{
	return ((t_tuple){
		m.val[0][0] * t.x + m.val[0][1] * t.y +
		m.val[0][2] * t.z + m.val[0][3] * t.w,
		m.val[1][0] * t.x + m.val[1][1] * t.y +
		m.val[1][2] * t.z + m.val[1][3] * t.w,
		m.val[2][0] * t.x + m.val[2][1] * t.y +
		m.val[2][2] * t.z + m.val[2][3] * t.w,
		m.val[3][0] * t.x + m.val[3][1] * t.y +
		m.val[3][2] * t.z + m.val[3][3] * t.w
	});
}
