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


void		init_anthill_one(t_anthill *h, int32_t nb_ants, int32_t max_flow)
{
	h->unsent = nb_ants - (nb_ants % max_flow);
	h->send_size = max_flow;
	h->total_exit = 0;
	h->total_enter = 0;
	h->nb_inside = 0;
	h->start_floor = 1;
	h->max_ant_index = 0;
	h->activated = LM_FALSE;
}

void		init_anthill_two(t_anthill *h, int32_t nb_ants, int32_t max_flow)
{
	h->unsent = nb_ants % max_flow;
	h->send_size = nb_ants % max_flow;
	h->total_exit = 0;
	h->total_enter = 0;
	h->nb_inside = 0;
	h->start_floor = 1;
	h->max_ant_index = 0;
	h->activated = LM_FALSE;
}

static int32_t	send_ants(t_anthill *h)
{
	int32_t		send;

	if (h->unsent)
	{
		send = h->send_size;
		h->unsent -= send;
	}
	else
		send = 0;
	return (send);
}

void		update_anthill_one_data(t_anthill *h, uint32_t send1)
{
	if (h->activated == LM_FALSE)
		return ;
	if (send1 == 0)
		h->start_floor++;
	h->total_enter += send1;
	h->nb_inside = h->total_enter - h->total_exit;
	h->max_ant_index = h->nb_inside + h->total_exit;
}

void		update_anthill_two_data(t_anthill *h2, uint32_t send2, t_anthill *h)
{
	if (h2->activated == LM_FALSE)
		return ;
	if (send2 == 0)
		h2->start_floor++;
	h2->total_enter += send2;
	h2->nb_inside = h2->total_enter - h2->total_exit;
	h2->max_ant_index = h2->nb_inside + h2->total_exit + h->max_ant_index;
}

void		print_ants(t_lemin *lem, t_circuits **cir_tab, int32_t tab_len)
{
	t_anthill	h1;
	t_anthill	h2;
	int32_t		send1;
	int32_t		send2;

	printf("\nTotal ants[%d]\n\n", lem->nb_ants);
	init_anthill_one(&h1, lem->nb_ants, tab_len);
	init_anthill_two(&h2, lem->nb_ants, tab_len);
	h1.activated = LM_TRUE;
	send2 = 0;
	while (h1.activated || h2.activated)
	{
		send1 = send_ants(&h1);
		if (send1 == 0)
			send2 = send_ants(&h2);
		if (send2 > 0)
			h2.activated = LM_TRUE;
		update_anthill_one_data(&h1, send1);
		update_anthill_two_data(&h2, send2, &h1);
		print_anthill_two(lem, cir_tab, tab_len, &h2);
		print_anthill(lem, cir_tab, tab_len, &h1);
		if (h1.nb_inside == 0)
			h1.activated = LM_FALSE;
		if (h2.nb_inside == 0)
			h2.activated = LM_FALSE;
		ft_putchar('\n');
	}
}
