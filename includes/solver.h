/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleblond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 15:36:05 by jleblond          #+#    #+#             */
/*   Updated: 2019/11/29 15:36:07 by jleblond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	SOLVER_H
# define SOLVER_H

# include "lem_in.h"


void		debug_print_address_lst(t_list **alst);
t_list		*address_list_new(t_node ** const new);
void		del_first_elem(t_list **alst);
uint8_t		not_in_address_lst(t_list *lst, t_node const *address);




# endif
