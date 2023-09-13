#include "../include/minirt.h"

double my_strtod(char *str)
{
	double divisor;
	double decimal;
	double result;
	int sign;

	sign = 1;
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	else if (*str == '+')
		str++;

	result = 0.0;
	while (ft_isdigit(*str))
	{
		result = result * 10.0 + (*str - '0');
		str++;
	}
	if (*str == '.')
	{
		str++;
		decimal = 0.0;
		divisor = 10.0;
		while (ft_isdigit(*str))
		{
			decimal += (*str - '0') / divisor;
			divisor *= 10.0;
			str++;
		}
		result += decimal;
	}
	return (sign * result);
}
