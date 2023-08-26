#include "minirt.h"

int main()
{
	t_matrix	A, B, C;

	A = (t_matrix){4, {
		{1, 2, 3, 4},
		{5, 6, 7, 8},
		{9, 8, 7, 6},
		{5, 4, 3, 2}
	}};

	B = (t_matrix){4, {
		{-2, 1, 2, 3},
		{3, 2, 1, -1},
		{4, 3, 6, 5},
		{1, 2, 7, 8}
	}};
	

	C = ft_multi_matrices(A, B);
	printf("The A x B matrix is:\n");
	ft_print_matrix(C);
}
