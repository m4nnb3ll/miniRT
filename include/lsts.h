#ifndef LSTS_H
#define	LSTS_H

void			ft_print_xs(t_xnode *xnode);
t_xnode		*ft_xnew(t_objnode *o, double x);
void			ft_xadd_back(t_xnode **xlst, t_xnode *n);
t_objnode	*ft_objnew(enum e_obj_type type);
void			ft_objadd_back(t_objnode **objlst, t_objnode *o);

#endif
