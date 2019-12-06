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
		ft_putstr("\n");
	}
}
