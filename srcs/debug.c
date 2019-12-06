/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleblond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 16:32:10 by jleblond          #+#    #+#             */
/*   Updated: 2019/12/04 16:32:13 by jleblond         ###   ########.fr       */
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

