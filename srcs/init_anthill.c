/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_anthill.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleblond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 20:56:43 by jleblond          #+#    #+#             */
/*   Updated: 2019/12/06 20:56:46 by jleblond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solver.h"

void		init_anthill_one(t_anthill *h, int32_t nb_ants, int32_t max_flow)
{
	h->unsent = nb_ants - (nb_ants % max_flow);
	h->send_size = max_flow;
	h->total_exit = 0;
	h->total_enter = 0;
	h->print_nb = 0;
	h->start_floor = 1;
	h->max_ant_index = 0;
	h->activated = LM_TRUE;
}

void		init_anthill_two(t_anthill *h, int32_t nb_ants, int32_t max_flow)
{
	h->unsent = nb_ants % max_flow;
	h->send_size = nb_ants % max_flow;
	h->total_exit = 0;
	h->total_enter = 0;
	h->print_nb = 0;
	h->start_floor = 1;
	h->max_ant_index = 0;
	h->activated = LM_FALSE;
}
