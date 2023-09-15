#include "../include/minirt.h"

void	ft_print_tuple(t_tuple a)
{
	printf("%f %f %f %f\n", a.x, a.y, a.z, a.w);
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

t_tuple	ft_negv(t_tuple a)
{
	return ((t_tuple){
		-a.x,
		-a.y,
		-a.z,
		0
	});
}

t_tuple	ft_sclv(t_tuple a, double sclr)
{
	return ((t_tuple){
		a.x * sclr,
		a.y * sclr,
		a.z * sclr,
		0
	});
}

double	ft_dot(t_tuple a, t_tuple b)
{
	return (
		a.x * b.x + a.y * b.y + a.z * b.z
	);
}

t_tuple	ft_cross(t_tuple a, t_tuple b)
{
	return (ft_vector(
		a.y * b.z - a.z * b.y,
		a.z * b.x - a.x * b.z,
		a.x * b.y - a.y * b.x
	));
}

double	ft_mag(t_tuple v)
{
	return (sqrt(pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2)));
}

t_tuple	ft_normalize(t_tuple v)
{
	double	mag;

	mag = ft_mag(v);
	return (ft_vector(v.x / mag, v.y / mag, v.z / mag));
}