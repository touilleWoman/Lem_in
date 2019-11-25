/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabih <naali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 13:50:24 by nabih             #+#    #+#             */
/*   Updated: 2019/11/25 14:26:32 by nabih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <solver.h>

static void				init_flow(t_lemin *lem, t_flow *f)
{
	t_node			*tmp;

	f->now = 0;
	tmp = get_node_in_hash(lem, lem->start);
	f->start = tmp->nb_paths;
	tmp = get_node_in_hash(lem, lem->end);
	f->end = tmp->nb_paths;
	f->max = (f->start <= f->end) ? f->start : f->end;
}

int8_t					solver(t_lemin *lem)
{
	t_flow			f;

	init_flow(lem, &f);
	return (LM_SUCCESS);
}
