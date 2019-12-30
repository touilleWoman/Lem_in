/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleblond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 17:25:51 by jleblond          #+#    #+#             */
/*   Updated: 2019/12/16 17:22:16 by nabih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solver.h"
#include "get_many_path.h"

// decommente pour voir le temps utilisé
void					solver(t_lemin *lem)
{
	int32_t			tab_len;
	t_circuits		**cir_tab;
	t_list			*ants;

	 // clock_t	start_t, finish_t; 
	 // start_t = clock();

	if ((tab_len = fulkerson_algo(lem, lem->nb_ants)) == 0)
		return ;

	 // finish_t = clock() - start_t;
	 // printf("fulkerson_algo time%f\n", (double)finish_t / CLOCKS_PER_SEC); 
// 	 start_t = clock(); 

	cir_tab = retrace_circuits(lem, tab_len);
	if (cir_tab)
	{
		/* finish_t = clock() - start_t; */
		/* printf("retrace_circuits time%f\n", (double)finish_t / CLOCKS_PER_SEC); */
		/* start_t = clock(); */

		ants = init_ant_lst(lem->nb_ants);

		/* finish_t = clock() - start_t; */
		/* printf("sort+antlst time%f\n", (double)finish_t / CLOCKS_PER_SEC); */
		/* start_t = clock(); */

		print_ants(lem, &ants, cir_tab, tab_len);

		/* finish_t = clock() - start_t; */
		/* printf("print path time%f\n", (double)finish_t / CLOCKS_PER_SEC); */
		
		free_cir_tab(cir_tab, tab_len);
	}
}
