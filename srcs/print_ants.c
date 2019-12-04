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

	if (h->activated == LM_FALSE)
		return ;
	i = 0;
	print_nb = h->nb_inside;
	ant_index = h->max_ant_index;
	floor = h->start_floor;
	while (print_nb > 0)
	{
		while (i < tab_len && print_nb > 0)
		{
			node_name = get_node_in_circuit(cir_tab[i]->addr, floor);
			if (!node_name)
				printf("can't get node name\n");
			// else
			// 	printf("name:%s\n", node_name);
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



static int32_t	send_ants(t_lemin *lem, int32_t wanted_max_flow)
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
	else
		sent = 0;
	return (sent);
}

static int32_t	send_ants_for_hill_two(t_lemin *lem, int32_t wanted_max_flow, int32_t sent1)
{
	static int32_t			one_round = 1;
	int32_t					sent2;

	if (one_round && (lem->nb_ants % wanted_max_flow) && sent1 == 0)
	{
		sent2 = lem->nb_ants % wanted_max_flow;
		one_round--;
	}
	else
		sent2 = 0;
	return (sent2);
}


void		update_anthill_data(t_anthill *h, uint32_t sent)
{
	if (h->activated == LM_FALSE)
		return ;
	if (sent == 0)
		h->start_floor++;
	h->total_enter += sent;
	h->nb_inside = h->total_enter - h->total_exit;
	h->max_ant_index = h->nb_inside + h->total_exit;
}

void		update_anthill_two_data(t_anthill *h2, uint32_t sent2, t_anthill *h)
{
	if (h2->activated == LM_FALSE)
		return ;
	if (sent2 == 0)
		h2->start_floor++;
	h2->total_enter += sent2;
	h2->nb_inside = h2->total_enter - h2->total_exit;
	h2->max_ant_index = h2->nb_inside + h2->total_exit + h->max_ant_index;
}

void		init_anthill(t_anthill *h)
{
	h->total_exit = 0;
	h->total_enter = 0;
	h->nb_inside = 0;
	h->start_floor = 1;
	h->activated = LM_FALSE;
}

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

int32_t		choose_shortest_circuit(t_circuits **cir_tab, int32_t tab_len, int32_t *best_cir, int32_t len)
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

int32_t			*choose_best_circuits(t_circuits **cir_tab, int32_t tab_len, int32_t best_cir_len)
{
	int32_t			*best_cir;
	int32_t			i;

	i = 0;
	best_cir = (int32_t*)malloc(sizeof(int32_t) * best_cir_len);
	if (!best_cir)
		return (NULL);
	while (i < best_cir_len)
	{
		best_cir[i] = choose_shortest_circuit(cir_tab, tab_len, best_cir, best_cir_len);
		i++;
	}
	return (best_cir);
}

void		print_anthill_two(t_lemin *lem, t_circuits **cir_tab, int32_t tab_len, t_anthill *h2)
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
	best_cir = choose_best_circuits(cir_tab, tab_len, best_cir_len);
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
				printf("Error !can't get node name\n"); // à modifier
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

void		print_ants(t_lemin *lem, t_circuits **cir_tab, int32_t tab_len)
{
	t_anthill	h;
	t_anthill	h2;
	int32_t		sent;
	int32_t		sent2;

	printf("\nTotal ants[%d]\n\n", lem->nb_ants);
	init_anthill(&h);
	init_anthill(&h2);
	h.activated = LM_TRUE;
	sent2 = 0;
	sent = 0;
	while (h.activated || h2.activated)
	{
		sent = send_ants(lem, tab_len);
		sent2 = send_ants_for_hill_two(lem, tab_len, sent);
		if (sent2 > 0)
			h2.activated = LM_TRUE;
		update_anthill_data(&h, sent);
		update_anthill_two_data(&h2, sent2, &h);
		print_anthill_two(lem, cir_tab, tab_len, &h2);
		print_anthill(lem, cir_tab, tab_len, &h);
		if (h.nb_inside == 0)
			h.activated = LM_FALSE;
		if (h2.nb_inside == 0)
			h2.activated = LM_FALSE;
		printf("\n");
	}
}
