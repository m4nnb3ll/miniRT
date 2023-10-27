/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lsts.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelayad <abelayad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 13:45:23 by abelayad          #+#    #+#             */
/*   Updated: 2023/10/26 19:38:49 by abelayad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LSTS_H
# define LSTS_H

void	ft_print_xs(t_xnode *xnode);
t_xnode	*ft_xnew(t_obj *o, double x);
void	ft_xadd_back(t_xnode **xlst, t_xnode *n);
t_light	*ft_lightnew(t_tuple position, t_color color);
void	ft_lightadd_back(t_light **lightlst, t_light *n);
t_obj	*ft_objnew(enum e_obj_type ot);
void	ft_objadd_back(t_obj **objlst, t_obj *n);

#endif
