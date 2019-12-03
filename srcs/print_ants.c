/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ants.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleblond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 12:45:26 by jleblond          #+#    #+#             */
/*   Updated: 2019/12/03 12:45:29 by jleblond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solver.h"

void		update_anthill_data(t_anthill *h)
{
	h->total_enter += h->new_enter;
	h->nb_inside = h->total_enter - h->total_exit;
}

void		print_line(uint32_t ant_index, char *node_name)
{
	printf("L%d-%s ", ant_index, node_name);
}


void		print_anthill_one(t_lemin *lem, t_list **cir_one, int32_t cir_nb, t_anthill *h)
{
	uint32_t 		ant_index;
	char			*node_name;
	int32_t			i;
	static uint32_t	initial_floor = 1;
	uint32_t		floor;

	i = 0;
	ant_index = h->nb_inside + h->total_exit;
	if (h->new_enter == 0)
		initial_floor++;
	floor = initial_floor;
	while (h->nb_inside)
	{
		while (i < cir_nb)
		{
			node_name = get_node_in_circuit(cir_one[i], floor);
			print_line(ant_index, node_name);
			if (ft_strcmp(node_name, (lem->end)->name) == 0)
				h->total_exit++;
			i++;
			ant_index--;
			(h->nb_inside)--;
		}
		i = 0;
		floor++;
	}
}

void		send_ants(t_lemin *lem, t_list **cir_one, t_list **cir_two, int32_t cir_nb[2])
{
	uint32_t	cir_one_round;
	t_anthill	h;

	(void)cir_two;
	cir_one_round = lem->nb_ants / cir_nb[0];
	h.total_exit = 0;
	h.total_enter = 0;
	while (LM_TRUE)
	{

		if (cir_one_round)
		{
			h.new_enter = cir_nb[0];
			cir_one_round--;
		}
		else if (cir_nb[1])
		{
			printf("entered circuit two!!!!!!!!!!!\n");
			h.new_enter = cir_nb[1];
		}
		else
			h.new_enter = 0;
		update_anthill_data(&h);
		if (h.nb_inside == 0)
			break ;
		print_anthill_one(lem, cir_one, cir_nb[0], &h);
		printf("\n");
	}
}
