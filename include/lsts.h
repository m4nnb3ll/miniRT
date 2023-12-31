/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lsts.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelayad <abelayad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 13:45:23 by abelayad          #+#    #+#             */
/*   Updated: 2023/12/04 09:52:59 by abelayad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LSTS_H
# define LSTS_H

t_xnode		*ft_xnew(t_obj *o, double x);
void		ft_xadd_back(t_xnode **xlst, t_xnode *n);
t_xnode		*ft_sort_xs(t_xnode *head);
t_contnode	*ft_contnew(t_obj *o);
void		ft_contadd_back(t_contnode **contlst, t_contnode *n);
t_contnode	*ft_containers_last(t_contnode *contlst);
bool		ft_containers_contain(t_contnode *contlst, t_obj *o);
void		ft_remove_container(t_contnode **head, t_obj *o);
t_obj		*ft_objnew(enum e_obj_type ot);
void		ft_objadd_back(t_obj **objlst, t_obj *n);
t_light		*ft_lightnew(t_tuple position, t_color color);
void		ft_lightadd_back(t_light **lightlst, t_light *n);

#endif
