/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleblond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 17:25:51 by jleblond          #+#    #+#             */
/*   Updated: 2020/01/06 13:41:39 by naali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solver.h"

void					solver(t_lemin *lem)
{
	int32_t			tab_len;
	t_circuits		**cir_tab;
	t_list			*ants;

	tab_len = fulkerson_algo(lem, lem->nb_ants);
	if (tab_len == 0)
	{
		ft_putstr_fd("ERROR\n", 2);
		return ;
	}
	cir_tab = retrace_circuits(lem, tab_len);
	if (cir_tab)
	{
		ants = NULL;
		ants = init_ant_lst(lem->nb_ants);
		print_ants(lem, &ants, cir_tab, tab_len);
		free_cir_tab(cir_tab, tab_len);
		ft_lstclear(&ants);
	}
}
