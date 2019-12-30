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

static uint8_t		iter_adja_of_current(t_node *current,
									t_list **open, uint32_t bfs_round)
{
	t_node		*adjacen_node;
	t_path		*p;

	p = current->path_lst;
	while (p)
	{
		adjacen_node = p->addr;
		if (!adjacen_node)
			return (LM_FALSE);
		if (p->flow > 0 && adjacen_node->visited != bfs_round)
		{	
			if (current->node_flow == 0 
				|| not_in_address_lst(current->forbidden_path, adjacen_node))
			{
				ft_lstadd_bot(open, address_list_new(&adjacen_node));
				adjacen_node->parent_addr = current;
				adjacen_node->visited = bfs_round;
			}
		}
		p = p->next;
	}
	return (LM_TRUE);
}

/*
** In this function, t_list stores, in lst->contente,
** the address of pointer of node.
** "open" are nodes to be evaluate, elements are always added to the bottom,
** and taken from the top to be evaluated,
** then delete top elem after evaluation.
** if "visited == lem->bfs_round", 
** it means node is already visited in this round of bfs,
** so we don't evaluate this node.
*/

static uint8_t		breadth_first_search(t_lemin *lem)
{
	uint8_t	ret;
	t_list	*open;
	t_node	**current;

	lem->bfs_round += 1;
	ret = LM_TRUE;
	open = address_list_new(&(lem->start));
	while (open && (current = get_top_elem(open)) && ret == LM_TRUE)
	{
		(*current)->visited = lem->bfs_round;
		if (*current == lem->end)
		{
			del_address_lst(&open);
			return (LM_TRUE);
		}
		ret = iter_adja_of_current(*current, &open, lem->bfs_round);
		del_top_elem(&open);
	}
	del_address_lst(&open);
	return (LM_FALSE);
}

static void			modify_residual_graph(t_lemin *lem)
{
	t_node		*parent;
	t_node		*child;

	child = lem->end;
	child->node_flow += 1;
	while (child != lem->start)
	{
		parent = child->parent_addr;
		parent->node_flow += 1;
		flow_plus_modif(parent, child, -1);
		flow_plus_modif(child, parent, 1);
		child = parent;
	}
}

/*
** after each round of bfs :
** 1. get_pathway():
** pathway is not the circuit of ants, but the trace of flow of
** fulkerson algo.
** 2. pathway_node_flow_update() :
** go through pathway for the first time to update node_flow, 
** if path_flow between two nodes == 2, meaning it will cancel precedent bfs, 
** therefore node_flow of these two nodes -=1.
** 3. cross_road_ok():
** check node_flow of all nodes on pathway.
** if node flow == 0, no crossroad, can pass
** if node flow == 1, can't pass
** if all nodes can pass, it will accepte this bfs by modifying residual graph.
** else, bfs is not accepted, it will find the bad path, 
** add it in fordidden_path of node, so that next round of bfs will 
** avoid this path
*/

uint32_t			fulkerson_algo(t_lemin *lem,
									uint32_t wanted_flow)
{
	uint32_t	max_flow;
	t_list		*pathway;

	max_flow = 0;
	while (breadth_first_search(lem))
	{
		pathway = get_pathway(lem);
		pathway_node_flow_update(pathway);
		if (cross_road_ok(pathway, lem))
		{
			modify_residual_graph(lem);
			max_flow++;
		}
		del_address_lst(&pathway);
		if (wanted_flow > 0 && max_flow == wanted_flow)
			break;
	}
	return (max_flow);
}
