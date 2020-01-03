/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleblond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 16:32:10 by jleblond          #+#    #+#             */
/*   Updated: 2020/01/03 10:19:44 by naali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solver.h"

void		debug_print_anttab(t_circuits **c, uint32_t *tab, uint32_t len)
{
	uint32_t	i;
	uint32_t	ants;

	i = 0;
	ants = 0;
	while (i < len)
	{
		printf("Floor[%d] => ants[%d] + node[%d] = %d\n", i, tab[i],
				c[i]->nb_floor, tab[i] + c[i]->nb_floor - 1);
		ants += tab[i];
		i++;
	}
	printf("Ants = %d\n", ants);
}

void		debug_print_address_lst(t_list *lst)
{
	t_node	*node;

	printf("address list:\n");
	while (lst != NULL)
	{
		node = *(t_node**)(lst->content);
		printf("[%s]\n", node->name);
		lst = lst->next;
	}
}

void		debug_print_circuits(t_circuits **cir_tab, uint32_t tab_len)
{
	uint32_t	i;
	t_node		*node;
	t_list		*cp;

	i = 0;
	while (i < tab_len)
	{
		printf("circuit[%d] has length of [%d]:\n", i, cir_tab[i]->nb_floor);
		cp = cir_tab[i]->addr;
		while (cp)
		{
			node = *(t_node**)(cp->content);
			cp = cp->next;
		}
		i++;
	}
}

/*
** printf("%s\n", node->name);
*/
