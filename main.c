#include "minirt.h"

int main()
{
	t_tuple		p;
	t_matrix	hq, fq;

	p = ft_point(0, 1, 0);
	hq = ft_rotate_z(PI/4);
	fq = ft_rotate_z(PI/2);
	ft_print_tuple(ft_trans_tuple(hq, p));
	ft_print_tuple(ft_trans_tuple(fq, p));
}
