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


// static uint32_t			remove_null(t_circuits **c, uint32_t len)
// {
// 	uint32_t		i;
// 	uint32_t		j;

// 	i = 0;
// 	while (i < len)
// 	{
// 		if (!(c[i]))
// 		{
// 			j = i + 1;
// 			while (j < len && !(c[i]))
// 			{
// 				ft_swap_ptr((void**)&(c[i]), (void**)&(c[j]));
// 				++j;
// 			}
// 		}
// 		++i;
// 	}
// 	i = 0;
// 	while (i < len && c[i])
// 		i++;
// 	return (i);
// }

// static uint32_t			duplicate_check(t_circuits **c, uint32_t len)
// {
// 	uint32_t		i;
// 	uint32_t		j;

// 	i = 0;
// 	while (i < len)
// 	{
// 		j = len - 1;
// 		while (j > i)
// 		{
// 			looking_for_duplicated_node(c, i, j);
// 			--j;
// 		}
// 		++i;
// 	}
// 	return (remove_null(c, len));
// }

static void				sort_path(t_circuits **c, uint32_t len)
{
	uint32_t		i;
	uint32_t		j;

	i = 0;
	while (i < len)
	{
		j = len - 1;
		while (j > i)
		{
			if (c[i]->nb_floor > c[j]->nb_floor)
				ft_swap_ptr((void**)&(c[i]), (void**)&(c[j]));
			--j;
		}
		++i;
	}
}

uint32_t	calculate_best_paths_nb(t_circuits **c, uint32_t tab_len, int32_t nb_ants)
{
	uint32_t	nb_paths;
	uint32_t	nb_lines;
	uint32_t	i;

	nb_paths = 1;
	nb_lines = nb_ants / nb_paths + c[0]->nb_floor - 1;
	i = 1;
	while (i < tab_len && c[i]->nb_floor < nb_lines)
	{
		nb_paths++;
		nb_lines = nb_ants / nb_paths + c[i]->nb_floor - 1;
		i++;
	}
	return (nb_paths);
}



// decommente pour voir le temps utilisé
void					solver(t_lemin *lem)
{
	int32_t			tab_len;
	t_circuits		**cir_tab;
	uint32_t		paths_nb;
	t_list			*ants;

	 clock_t	start_t, finish_t; 
	 start_t = clock();
	if ((tab_len = fulkerson_algo(lem, lem->nb_ants)) == 0)
		return ;
	if ((cir_tab = init_cir_tab(tab_len)) == NULL)
		return ;
	if (retrace_circuits(lem, tab_len, cir_tab)== LM_FALSE)
		return ;
	paths_nb = calculate_best_paths_nb(cir_tab, tab_len, lem->nb_ants);
	free_cir_tab(cir_tab, tab_len);

	if ((tab_len = fulkerson_algo(lem, paths_nb)) == 0)
		return ;

	if ((cir_tab = init_cir_tab(tab_len)) == NULL)
		return ;


	 finish_t = clock() - start_t;
	 printf("fulkerson_algo time%f\n", (double)finish_t / CLOCKS_PER_SEC); 
// 	 start_t = clock(); 

	if (retrace_circuits(lem, tab_len, cir_tab))
	{

		/* finish_t = clock() - start_t; */
		/* printf("retrace_circuits time%f\n", (double)finish_t / CLOCKS_PER_SEC); */
		/* start_t = clock(); */
		// tab_len = duplicate_check(cir_tab, tab_len);
		sort_path(cir_tab, tab_len);
		// debug_print_circuits(cir_tab, tab_len);

		// app_max = get_appro_max(cir_tab, tab_len, lem->nb_ants);// Calcul approximatif du nombre de ligne
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
