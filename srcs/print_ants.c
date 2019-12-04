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

void		print_line(uint32_t ant_index, char *node_name)
{
	printf("L%d-%s ", ant_index, node_name);
}

void		print_anthill(t_lemin *lem, t_circuits **cir_tab, int32_t tab_len, t_anthill *h)
{
	uint32_t 		ant_index;
	char			*node_name;
	int32_t			i;
	uint32_t		floor;
	uint32_t		print_nb;

	i = 0;
	print_nb = h->nb_inside;
	ant_index = h->max_ant_index;
	floor = h->start_floor;
	// debug_print_struct(h);

	while (print_nb)
	{
		while (i < tab_len)
		{
			node_name = get_node_in_circuit(cir_tab[i]->addr, floor);
			if (node_name == NULL)
				return ;
			print_line(ant_index, node_name);
			if (ft_strcmp(node_name, (lem->end)->name) == 0)
			{
				h->total_exit++;
				h->nb_inside--;
			}
			i++;
			ant_index--;
			print_nb--;
			// printf("i:%d\n",i);

		}
		i = 0;
		floor++;
	}
}

void		update_anthill_data(t_anthill *h)
{
	if (h->new_enter == 0)
		h->start_floor++;
	h->total_enter += h->new_enter;
	h->nb_inside = h->total_enter - h->total_exit;
	h->max_ant_index = h->nb_inside + h->total_exit;
	if (h->nb_inside)
		h->activated = LM_TRUE;
	else
		h->activated = LM_FALSE;

}

static int32_t	send_ants_cir_one(t_lemin *lem, int32_t wanted_max_flow)
{
	static int32_t			count = 0;
	int32_t					max_flow_round;
	int32_t					sent;

	max_flow_round = lem->nb_ants / wanted_max_flow;
	if (count < max_flow_round)
	{
		sent = wanted_max_flow;
		count++;
	}
	else if (count == max_flow_round && lem->nb_ants % wanted_max_flow)
	{
		sent = lem->nb_ants % wanted_max_flow;
		count++;
	}
	else
		sent = 0;
	return (sent);
}


void		init_anthill(t_anthill *h)
{
	h->total_exit = 0;
	h->total_enter = 0;
	h->nb_inside = 0;
	h->start_floor = 1;
	h->activated = LM_FALSE;
}

void		print_ants(t_lemin *lem, t_circuits **cir_tab, int32_t tab_len)
{
	t_anthill	h;

	printf("\nTotal ants[%d]\n\n", lem->nb_ants);
	init_anthill(&h);
	h.activated = LM_TRUE;
	// int32_t	n = 0;
	while (h.activated)
	{
		h.new_enter = send_ants_cir_one(lem, tab_len);
		// debug_print_struct(&h);
		update_anthill_data(&h);
		// debug_print_struct(&h);

		print_anthill(lem, cir_tab, tab_len, &h);
		printf("\n");
		// n++;
		// if (n> 5 )
		// {
		// 	return ;
		// }

	}
}
