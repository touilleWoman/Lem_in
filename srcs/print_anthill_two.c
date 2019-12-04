/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_anthill_two.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleblond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 19:13:26 by jleblond          #+#    #+#             */
/*   Updated: 2019/12/04 19:13:29 by jleblond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solver.h"

uint32_t	not_already_in_best_cir(int32_t *best_cir, int32_t len, int32_t chosen)
{
	int32_t	i;

	i = 0;
	while (i < len)
	{
		if (best_cir[i] == chosen)
			return (LM_FALSE);
		i++;
	}
	return (LM_TRUE);
}

int32_t		choose_shortest(t_circuits **cir_tab, int32_t tab_len, int32_t *best_cir, int32_t len)
{
	int32_t	choose;
	uint32_t shortest;
	int32_t min;

	choose = 0;
	min = 0;
	while (choose < tab_len)
	{
		if (choose == 0)
			shortest = cir_tab[choose]->nb_floor;
		if (cir_tab[choose]->nb_floor < shortest && not_already_in_best_cir(best_cir, len, choose))
		{
			shortest = cir_tab[choose]->nb_floor;
			min = choose;
		}
		choose++;
	}
	return (min);
}

int32_t			*fill_best_circuits(t_circuits **cir_tab, int32_t tab_len, int32_t best_cir_len)
{
	int32_t			*best_cir;
	int32_t			i;

	i = 0;
	best_cir = (int32_t*)malloc(sizeof(int32_t) * best_cir_len);
	if (!best_cir)
		return (NULL);
	while (i < best_cir_len)
	{
		best_cir[i] = choose_shortest(cir_tab, tab_len, best_cir, best_cir_len);
		i++;
	}
	return (best_cir);
}

void		print_anthill_two(t_lemin *lem, t_circuits **cir_tab,
							int32_t tab_len, t_anthill *h2)
{
	uint32_t 		ant_index;
	char			*node_name;
	int32_t			i;
	uint32_t		floor;
	uint32_t		print_nb;
	int32_t			*best_cir;
	int32_t			index;
	int32_t			best_cir_len;


	if (h2->activated == LM_FALSE)
		return ;
	best_cir_len = lem->nb_ants % tab_len;
	best_cir = fill_best_circuits(cir_tab, tab_len, best_cir_len); //à free plus tard
	i = 0;
	print_nb = h2->nb_inside;
	ant_index = h2->max_ant_index;
	floor = h2->start_floor;
	while (print_nb > 0)
	{
		while (i < best_cir_len && print_nb > 0)
		{
			index = best_cir[i];
			node_name = get_node_in_circuit(cir_tab[index]->addr, floor);
			if (!node_name)
				printf("Error !can't get node name\n"); // à recrire
			print_line(ant_index, node_name);
			if (ft_strcmp(node_name, (lem->end)->name) == 0)
			{
				h2->total_exit++;
				h2->nb_inside--;
			}
			i++;
			ant_index--;
			print_nb--;
		}
		i = 0;
		floor++;
	}
}
