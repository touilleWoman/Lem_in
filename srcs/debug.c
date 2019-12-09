/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleblond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 16:32:10 by jleblond          #+#    #+#             */
/*   Updated: 2019/12/09 07:22:23 by nabih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solver.h"


void		debug_print_circuits(t_circuits **cir_tab, uint32_t tab_len)
{
	uint32_t		i;
	t_node	*node;
	t_list	*cp;

	i = 0;
	while (i < tab_len)
	{
		printf("circuit[%d] has length of [%d]:\n", i, cir_tab[i]->nb_floor);
		cp = cir_tab[i]->addr;
		while (cp)
		{
			node = *(t_node**)(cp->content);
			printf("%s\n", node->name);
			cp = cp->next;
		}
		i++;
	}
}

/*
** Cherche le meilleure ratio pour le nombre
** de ligne a afficher a chaque tour
*/
uint32_t				how_many_path(t_circuits **c, uint32_t len, uint32_t ants)
{
	uint32_t		not_use;
	uint32_t		ratio;
	uint32_t		old;
	uint32_t		new;
//	uint32_t		old_len;

	not_use = 0;
	old = 0;
	new = 0;
	ratio = ants / len;
	old = c[--len]->nb_floor + (ratio - 1);
//	old_len = len;
	while (--len > 0)
	{
		ratio = ants / (len + 1);
		if (ratio > 0)
		{
			new = c[len]->nb_floor + (ratio - 1);
			if (new <= old)
			{
				/* if (new == old && c[len]->nb_floor == c[old_len]->nb_floor) */
				/* 	not_use--; */
//				old_len = len;
				old = new;
				not_use++;
			}
		}
	}
	return (not_use);
}
