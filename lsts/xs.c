#include "minirt.h"

void	ft_print_xs(t_xnode *xnode)
{
	printf("Printing intersections:\n");
	while (xnode)
	{
		printf("the obj is: %p\nthe x is: %f\n", xnode -> o, xnode -> x);
		xnode = xnode -> next;
	}
}

t_xnode	*ft_xnew(t_objnode *o, double x)
{
	t_xnode	*new;

	new = ft_calloc(1, sizeof(t_xnode));
	if (!new)
		return (NULL);
	new -> o = o;
	new -> x = x;
	return (new);
}

void	ft_xadd_back(t_xnode **xlst, t_xnode *n)
{
	t_xnode	*tmp;

	if (!xlst || !n)
		return ;
	if (!*xlst)
		*xlst = n;
	else
	{
		tmp = *xlst;
		while (tmp -> next)
			tmp = tmp -> next;
		tmp -> next = n;
	}
}
