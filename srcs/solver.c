/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleblond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 17:25:51 by jleblond          #+#    #+#             */
/*   Updated: 2019/11/29 17:25:54 by jleblond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solver.h"

int8_t			flow_plus_modif(t_node *enter, t_node *exit, int8_t modif)
{
	t_path	*p;

	p = enter->path_lst;
	while(p)
	{
		if (ft_strcmp(p->name, exit->name) == 0)
		{
			// printf("flow of pathname[%s] changed from [%d] to [%d]\n", p->name, p->flow, modif);
			p->flow += modif;
			return (LM_SUCCESS);
		}
		p = p->next;
	}
	return (LM_ERROR);
}

/*
** cir_nb represents the number of circuits in cir_one,
** it's equal to nb of flow returned by fulkerson_algo().
*/

void		solver(t_lemin *lem)
{
	int32_t			cir_nb;
	t_list			**cir;

	cir_nb = fulkerson_algo(lem, lem->nb_ants);
	cir = retrace_circuits(lem, cir_nb);
	print_ants(lem, cir, cir_nb);
	free_circuits(cir, cir_nb);
}
