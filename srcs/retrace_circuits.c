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

void		debug_print_circuits(t_list **circuits, int nb_paths)
{
	int		i;
	t_node	*node;
	t_list	*cp;

	i = 0;
	while (i < nb_paths)
	{
		printf("circuit[%d]:\n", i);
		cp = circuits[i];
		while (cp)
		{
			node = *(t_node**)(cp->content);
			printf("%s\n", node->name);
			cp = cp->next;
		}
		i++;
	}
}

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

/*
** circuits are array of circuits found, array len = cir_nb
** value stored in array is address of poiter of t_node
*/

t_list		**retrace_circuits(t_lemin *lem, uint32_t cir_nb)
{
	t_list			**circuits;
	uint32_t		i;
	t_node			*child;
	t_node			*parent;
	char			*parent_name;

	i = 0;
	circuits = (t_list**)malloc(sizeof(t_list*) * cir_nb);
	if (!circuits)
		return (NULL);
	ft_bzero(circuits, sizeof(t_list*) * cir_nb);
	while (i < cir_nb)
	{
		child = lem->end;
		circuits[i] = address_list_new(&child);
		if (!circuits[i])
		{
			free_circuits(circuits, cir_nb);
			return (NULL);
		}
		while (child != lem->start)
		{
			if ((parent_name = get_occupied_node(child)) == NULL)
			{
				free_circuits(circuits, cir_nb);
				return (NULL);
			}
			parent = get_node_in_hash(lem, parent_name);
			ft_lstadd_top(&(circuits[i]), address_list_new(&parent));
			flow_plus_modif(child, parent, -1);
			flow_plus_modif(parent, child, 1);
			child = parent;
		}
		i++;
	}
	return (circuits);
}
