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

void		debug_print_struct(t_anthill *h)
{
	printf("new_enter=[%d], total_exit=[%d], total_enter=[%d], nb_inside[%d]\n", h->new_enter, h->total_exit, h->total_enter, h->nb_inside );
}

void		print_anthill_two(t_lemin *lem, t_list **cir_two, int32_t cir_nb, t_anthill *h)
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
	// printf("nb_inside:%d, max_ant_index:%d, start_floor%d\n",h->nb_inside , h->max_ant_index, h->start_floor );
	while (print_nb)
	{
		while (i < cir_nb)
		{
			node_name = get_node_in_circuit(cir_two[i], floor);
			print_line(ant_index, node_name);
			if (ft_strcmp(node_name, (lem->end)->name) == 0)
			{
				h->total_exit++;
				h->nb_inside--;
			}
			i++;
			ant_index--;
			print_nb--;
		}
		i = 0;
		floor++;
	}
}

void		print_anthill_one(t_lemin *lem, t_list **cir_one, int32_t cir_nb, t_anthill *h)
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
	while (print_nb)
	{
		while (i < cir_nb)
		{
			node_name = get_node_in_circuit(cir_one[i], floor);
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

void		update_anthill_two_data(t_anthill *h2, t_anthill *h1)
{
	if (h2->new_enter == 0)
		h2->start_floor++;
	h2->total_enter += h2->new_enter;
	h2->nb_inside = h2->total_enter - h2->total_exit;
	h2->max_ant_index = h1->max_ant_index + h2->nb_inside + h2->total_exit;
	if (h2->nb_inside)
		h2->activated = LM_TRUE;
	else
		h2->activated = LM_FALSE;
}

static int32_t	send_ants_cir_one(t_lemin *lem, int32_t cir_nb)
{
	int32_t			sent;
	static	int32_t	cir_one_round = 0;

	if (cir_one_round < lem->nb_ants / cir_nb)
	{
		sent = cir_nb;
		cir_one_round++;
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

void		print_ants(t_lemin *lem, t_list **cir, int32_t cir_nb)
{
	t_anthill	h;

	printf("\nTotal ants[%d]\n\n", lem->nb_ants);
	init_anthill(&h);
	h.activated = LM_TRUE;
	while (h.activated)
	{
		h.new_enter = send_ants_cir_one(lem, cir_nb);
		update_anthill_data(&h);
		print_anthill_one(lem, cir, cir_nb, &h);
		printf("\n");
	}
}
