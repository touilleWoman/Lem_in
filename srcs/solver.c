/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabih <naali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 13:50:24 by nabih             #+#    #+#             */
/*   Updated: 2019/11/26 15:52:31 by naali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <solver.h>

static void				init_solve(t_lemin *lem, t_solver *sol)
{
	sol->nb_node = 0;
	sol->op_lst = ;
	sol->cl_lst = NULL;
	sol->next = NULL;
}

int8_t					solver(t_lemin *lem)
{
	t_flow			f;

	init_flow(lem, &f);
	return (LM_SUCCESS);
}
