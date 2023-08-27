#include "minirt.h"

t_matrix	ft_translate(double x, double y, double z)
{
	return ((t_matrix){
		4, {
			{1, 0, 0, x},
			{0, 1, 0, y},
			{0, 0, 1, z},
			{0, 0, 0, 1}
		}
	});
}

t_matrix	ft_scale(double x, double y, double z)
{
	return ((t_matrix){
		4, {
			{x, 0, 0, 0},
			{0, y, 0, 0},
			{0, 0, z, 0},
			{0, 0, 0, 1}
		}
	});
}

t_matrix	ft_rotate_x(double rad)
{
	return ((t_matrix){
		4, {
			{1, 0, 0, 0},
			{0, cos(rad), -sin(rad), 0},
			{0, sin(rad), cos(rad), 0},
			{0, 0, 0, 1}
		}
	});
}

t_matrix	ft_rotate_y(double rad)
{
	return ((t_matrix){
		4, {
			{cos(rad), 0, sin(rad), 0},
			{0, 1, 0, 0},
			{-sin(rad), 0, cos(rad), 0},
			{0, 0, 0, 1}
		}
	});
}

t_matrix	ft_rotate_z(double rad)
{
	return ((t_matrix){
		4, {
			{cos(rad), -sin(rad), 0, 0},
			{sin(rad), cos(rad), 0, 0},
			{0, 0, 1, 0},
			{0, 0, 0, 1}
		}
	});
}

t_tuple	ft_trans_tuple(t_matrix m, t_tuple t)
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
