#include "minirt.h"

t_objnode	*ft_objnew(enum e_obj_type type)
{
	t_objnode	*new;

	new = ft_calloc(1, sizeof(t_objnode));
	if (!new)
		return (NULL);
	new -> type = type;
	new -> transform_inverse = g_identity_matrix;
	new -> material = ft_material();
	return (new);
}

void	ft_objadd_back(t_objnode **objlst, t_objnode *o)
{
	t_objnode	*tmp;

	if (!objlst || !o)
		return ;
	if (!*objlst)
		*objlst = o;
	else
	{
		tmp = *objlst;
		while (tmp -> next)
			tmp = tmp -> next;
		tmp -> next = o;
	}
}
