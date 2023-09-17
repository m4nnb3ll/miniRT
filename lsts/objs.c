#include "minirt.h"

// t_obj	*ft_objnew(enum e_obj_type type, void *props)
// {
// 	t_obj	*new;

// 	new = ft_calloc(1, sizeof(t_obj));
// 	if (!new)
// 		return (NULL);
// 	new -> type = type;
// 	new -> transform_inverse = g_identity_matrix;
// 	new -> material = ft_material();
// 	new -> props = props;
// 	return (new);
// }

// void	ft_objadd_back(t_obj **objlst, t_obj *o)
// {
// 	t_obj	*tmp;

// 	if (!objlst || !o)
// 		return ;
// 	if (!*objlst)
// 		*objlst = o;
// 	else
// 	{
// 		tmp = *objlst;
// 		while (tmp -> next)
// 			tmp = tmp -> next;
// 		tmp -> next = o;
// 	}
// }
