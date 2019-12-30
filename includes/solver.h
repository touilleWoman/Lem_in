/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleblond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 15:36:05 by jleblond          #+#    #+#             */
/*   Updated: 2019/12/18 15:12:06 by naali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOLVER_H
# define SOLVER_H

# include "lem_in.h"

typedef	struct	s_circuits
{
	uint32_t	nb_floor;
	t_list		*addr;
}				t_circuits;

typedef struct	s_manypth
{
	uint32_t	not_use;
	uint32_t	ratio;
	uint32_t	old;
	uint32_t	new;
	uint32_t	diff;
	uint32_t	old_diff;
}				t_manypth;

t_list			*address_list_new(t_node **const new);
void			del_top_elem(t_list **alst);
t_node			**get_top_elem(t_list *lst);
uint8_t			not_in_address_lst(t_list *lst, t_node const *address);
void			print_ants(t_lemin *lem, t_list **ants,
							t_circuits **cir_tab, int32_t tab_len);
uint32_t		fulkerson_algo(t_lemin *lem, uint32_t wanted_flow);
int8_t			flow_plus_modif(t_node *enter, t_node *exit, int8_t modif);
t_circuits		**retrace_circuits(t_lemin *lem, uint32_t tab_len);
void			free_cir_tab(t_circuits **cir_tab, uint32_t tab_len);
uint32_t		how_many_path(t_circuits **c, uint32_t len,
								uint32_t ants);
uint8_t			cross_road_ok(t_list *lst, t_lemin *lem);
t_list			*get_pathway(t_lemin *lem);
void			pathway_node_flow_update(t_list *lst);


/*
** à supprimer functions debug à la fin
*/
void			debug_print_circuits(t_circuits **cir_tab, uint32_t tab_len);
void			debug_print_address_lst(t_list *lst);
void			debug_print_anttab(t_circuits **c, uint32_t *tab,
									uint32_t len);

#endif
