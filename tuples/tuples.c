#include "minirt.h"

void	ft_print_tuple(t_tuple a)
{
	printf("%.f %.f %.f %.f\n", a.x, a.y, a.z, a.w);
}

t_tuple	ft_point(double x, double y, double z)
{
	return ((t_tuple){ x, y, z, 1 });
}

t_tuple	ft_vector(double x, double y, double z)
{
	return ((t_tuple){ x, y, z, 0 });
}

t_tuple	ft_add_tuples(t_tuple a, t_tuple b)
{
	return ((t_tuple){
		a.x + b.x,
		a.y + b.y,
		a.z + b.z,
		a.w + b.w
	});
}

t_tuple	ft_sub_tuples(t_tuple a, t_tuple b)
{
	return ((t_tuple){
		a.x - b.x,
		a.y - b.y,
		a.z - b.z,
		a.w - b.w
	});
}

t_tuple	ft_neg_vec(t_tuple a)
{
	return ((t_tuple){
		-a.x,
		-a.y,
		-a.z,
		0
	});
}

t_tuple	ft_scl_vec(t_tuple a, double sclr)
{
	return ((t_tuple){
		a.x * sclr,
		a.y * sclr,
		a.z * sclr,
		0
	});
}
