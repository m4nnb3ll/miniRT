#include "minirt.h"

void	ft_print_ray(t_ray r)
{
	printf("ray's origin: ");
	ft_print_tuple(r.origin);
	printf("ray's direction: ");
	ft_print_tuple(r.direction);
}

t_ray	ft_ray(t_tuple origin, t_tuple direction)
{
	return ((t_ray){ origin, direction });
}

t_tuple	ft_pos_on_ray(t_ray r, double x)
{
	return (ft_add_tuples(r.origin, ft_sclv(r.direction, x)));
}

t_ray	ft_transform_ray(t_matrix m, t_ray r)
{
	r.origin = ft_transform_tuple(m, r.origin);
	r.direction = ft_transform_tuple(m, r.direction);
	// if normalizing the direction after the transform doesn't affect the others
	// you can add it here.
	return (r);
}
