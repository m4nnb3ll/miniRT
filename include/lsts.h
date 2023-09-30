/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lsts.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelayad <abelayad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 13:45:23 by abelayad          #+#    #+#             */
/*   Updated: 2023/09/28 13:32:46 by abelayad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LSTS_H
# define LSTS_H

void		ft_print_xs(t_xnode *xnode);
t_xnode		*ft_xnew(t_objnode *o, double x);
void		ft_xadd_back(t_xnode **xlst, t_xnode *n);
t_xnode		*ft_sort_xs(t_xnode *head);
t_contnode	*ft_contnew(t_objnode *o);
void		ft_contadd_back(t_contnode **contlst, t_contnode *n);
t_contnode	*ft_containers_last(t_contnode *contlst);
bool		ft_containers_contain(t_contnode *contlst, t_objnode *o);
void		ft_remove_container(t_contnode **head, t_objnode *o);

#endif
