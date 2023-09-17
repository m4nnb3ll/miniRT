#ifndef LSTS_H
#define	LSTS_H

void			ft_print_xs(t_xnode *xnode);
t_xnode		*ft_xnew(t_obj *o, double x);
void			ft_xadd_back(t_xnode **xlst, t_xnode *n);
// t_obj	*ft_objnew(enum e_obj_type type, void *props);
// void			ft_objadd_back(t_obj **objlst, t_obj *o);

#endif
