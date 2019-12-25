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



// uint32_t	calculate_best_paths_nb(t_circuits **c, uint32_t tab_len, int32_t nb_ants)
// {
// 	uint32_t	nb_paths;
// 	uint32_t	nb_lines;
// 	uint32_t	i;

// 	nb_paths = 1;
// 	nb_lines = nb_ants / nb_paths + c[0]->nb_floor - 1;
// 	i = 1;
// 	while (i < tab_len && c[i]->nb_floor < nb_lines)
// 	{
// 		nb_paths++;
// 		nb_lines = nb_ants / nb_paths + c[i]->nb_floor - 1;
// 		i++;
// 	}
// 	return (nb_paths);
// }



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
	if ((cir_tab = init_cir_tab(tab_len)) == NULL)
		return ;

	 // finish_t = clock() - start_t;
	 // printf("fulkerson_algo time%f\n", (double)finish_t / CLOCKS_PER_SEC); 
// 	 start_t = clock(); 

	if (retrace_circuits(lem, tab_len, cir_tab))
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

	}
	free_cir_tab(cir_tab, tab_len);
}
