/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fulkerson_algo.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleblond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 11:45:10 by jleblond          #+#    #+#             */
/*   Updated: 2019/12/18 13:54:45 by naali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solver.h"

static t_node		**get_top_elem(t_list *lst)
{
	t_node	**ret;

	ret = NULL;
	if (lst != NULL)
		ret = (t_node**)(lst->content);
	return (ret);
}



static uint8_t		iter_adja_of_current(t_node *current,
									t_list **open, uint32_t loop)
{
	t_node		*adjacen_node;
	t_path		*p;

	p = current->path_lst;
	while (p)
	{
		adjacen_node = p->addr;
		if (!adjacen_node)
			return (LM_FALSE);
		if (p->flow > 0 && adjacen_node->visited != loop)
		{
			adjacen_node->visited = loop;
			ft_lstadd_bot(open, address_list_new(&adjacen_node));
			adjacen_node->parent_addr = current;
		}
		p = p->next;
	}
	return (LM_TRUE);
}


/*
** In this function, t_list stores, in lst->contente,
** the address of pointer of node.
** "open" are nodes to be evaluate, elements are always added to the end,
** and taken from the top to be evaluated,
** then delete top elem after evaluation.
** if "visited == loop", means node is already visited this round of bfs,,
** so we don't evaluate this node.
*/

static uint8_t		breadth_first_search(t_lemin *lem, uint32_t loop)
{
	uint8_t	ret;
	t_list	*open;
	t_node	**current;

	ret = LM_TRUE;
	open = address_list_new(&(lem->start));
	while (open && (current = get_top_elem(open)) && ret == LM_TRUE)
	{
		(*current)->visited = loop;
		if (*current == lem->end)
		{
			del_address_lst(open);
			return (LM_TRUE);
		}
		ret = iter_adja_of_current(*current, &open, loop);
		del_top_elem(&open);
	}
	del_address_lst(open);
	return (LM_FALSE);
}



void		modify_residual_graph(t_lemin *lem)
{
	t_node		*parent;
	t_node		*child;

	child = lem->end;
	child->node_flow += 1;
	while (child != lem->start)
	{
		parent = child->parent_addr;
		flow_plus_modif(parent, child, -1);
		flow_plus_modif(child, parent, 1);
		child = parent;
		child->node_flow += 1;
	}
}

/*
** wanted_flow is the maximum flow that we want,
** it will limite max_flow returned
** if lem->nb_ants < max_flow, then the flow returned is wanted_flow,
** else, the flow returned is the maximum flow that anthill can provide.
** but if wanted_flow == 0, it will return the actual maximum flow
** loop represents how many times bfs has been lauched
*/

uint32_t			fulkerson_algo(t_lemin *lem,
									uint32_t wanted_flow)
{
	uint32_t	max_flow;

	static uint32_t	loop = 1;

	max_flow = 0;
	while (breadth_first_search(lem, loop))
	{
		loop++;
		max_flow++;
		// if (node_flow_correct(lem))
		modify_residual_graph(lem);
		if (wanted_flow > 0 && max_flow == wanted_flow)
			return (wanted_flow);
	}
	printf("loop ===%d\n", loop);
	return (max_flow);
}
