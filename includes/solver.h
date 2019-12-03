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

# define CIRCUIT_ONE 1
# define CIRCUIT_TWO 2


typedef	struct	s_anthill
{
	uint32_t	new_enter;
	uint32_t	total_exit;
	uint32_t	total_enter;
	uint32_t	nb_inside;
}				t_anthill;

void		debug_print_address_lst(t_list **alst);
t_list		*address_list_new(t_node ** const new);
void		del_top_elem(t_list **alst);
void		del_address_lst(t_list *lst);
uint8_t		not_in_address_lst(t_list *lst, t_node const *address);
char		*get_node_in_circuit(t_list *cir, uint32_t floor);
void		send_ants(t_lemin *lem, t_list **cir_one, t_list **cir_two, int32_t cir_nb[2]);





# endif
