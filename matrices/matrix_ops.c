/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_ops.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelayad <abelayad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 15:20:10 by abelayad          #+#    #+#             */
/*   Updated: 2023/09/20 15:30:22 by abelayad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

const t_matrix	g_identity_matrix = {4,
{{1, 0, 0, 0},
{0, 1, 0, 0},
{0, 0, 1, 0},
{0, 0, 0, 1}}
};

t_matrix	ft_matrix_scl(t_matrix m, double scl)
{
	int	i;
	int	j;

	i = 0;
	while (i < m.size && i < 3)
	{
		j = 0;
		while (j < m.size && j < 3)
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
	int			i;
	int			j;

	c = g_identity_matrix;
	i = 0;
	while (i < c.size)
	{
		j = 0;
		while (j < c.size)
		{
			c.val[i][j] = a.val[i][0] * b.val[0][j] + a.val[i][1] * b.val[1][j]
				+ a.val[i][2] * b.val[2][j] + a.val[i][3] * b.val[3][j];
			j++;
		}
		i++;
	}
	return (c);
}

t_matrix	ft_transpose(t_matrix m)
{
	int			i;
	int			j;
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

t_matrix	ft_inverse(t_matrix original)
{
	int			i;
	int			j;
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
