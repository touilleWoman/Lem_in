/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   retrace_circuits.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleblond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 13:34:02 by jleblond          #+#    #+#             */
/*   Updated: 2019/12/04 13:34:12 by jleblond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solver.h"


char			*get_occupied_node(t_node *enter)
{
	t_path		*p;

	p = enter->path_lst;
	while(p)
	{
		if (p->flow == 2)
			return (p->name);
		p = p->next;
	}
	return (NULL);
}

char		*get_node_in_circuit(t_list *cir, uint32_t floor)
{
	t_node *node;

	while (cir && floor != 0)
	{
		cir = cir->next;
		floor--;
	}
	if (cir)
	{
		node = *((t_node**)(cir->content));
		return (node->name);
	}
	return (NULL);
}

t_circuits		**init_cir_tab(uint32_t tab_len)
{
	t_circuits		**cir_tab;
	uint32_t		i;

	i = 0;
	cir_tab = (t_circuits**)malloc(sizeof(t_circuits*) * tab_len);
	if (!cir_tab)
		return (NULL);
	while (i < tab_len)
	{
		cir_tab[i] = (t_circuits*)malloc(sizeof(t_circuits));
		if (!cir_tab[i])
		{
			free_cir_tab(cir_tab, tab_len);
			return (NULL);
		}
		cir_tab[i]->addr = NULL;
		cir_tab[i]->nb_floor = 0;
		i++;
	}
	return (cir_tab);
}

/*
** circuits are array of circuits found, array len = tab_len
** value stored in array is address of poiter of t_node
*/

t_circuits		**retrace_circuits(t_lemin *lem, uint32_t tab_len)
{
	t_circuits		**cir_tab;
	uint32_t		i;
	t_node			*child;
	t_node			*parent;
	char			*parent_name;
	uint32_t		nb_floor;

	i = 0;
	nb_floor = 0;
	cir_tab = init_cir_tab(tab_len);
	if (!cir_tab)
		return (NULL);
	while (i < tab_len)
	{
		child = lem->end;
		cir_tab[i]->addr = address_list_new(&child);
		if (!cir_tab[i])
		{
			free_cir_tab(cir_tab, tab_len);
			return (NULL);
		}
		while (child != lem->start)
		{
			parent_name = get_occupied_node(child);
			// if ((parent_name = get_occupied_node(child)) == NULL)
			// {
			// 	free_cir_tab(cir_tab, tab_len);
			// 	return (NULL);
			// }
			parent = get_node_in_hash(lem, parent_name);
			ft_lstadd_top(&(cir_tab[i]->addr), address_list_new(&parent));
			flow_plus_modif(child, parent, -1);
			flow_plus_modif(parent, child, 1);
			child = parent;
			nb_floor++;
		}
		cir_tab[i]->nb_floor = nb_floor;
		nb_floor = 0;
		i++;
	}
	return (cir_tab);
}
