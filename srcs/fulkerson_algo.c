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
		// if (ft_strcmp(current->name, "5") == 0)
		// {
		// 	printf("adjacen_node of 5 is [%s], pflow[%d], visited[%d] vs bfs_round[%d]\n", adjacen_node->name, p->flow, adjacen_node->visited, bfs_round);
		// }
		if (p->flow > 0 && adjacen_node->visited != bfs_round)
		{	


			if (current->node_flow == 0 || not_in_address_lst(current->forbidden_path, adjacen_node))
			{
				printf("%s\n", adjacen_node->name);
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
** "open" are nodes to be evaluate, elements are always added to the end,
** and taken from the top to be evaluated,
** then delete top elem after evaluation.
** if "visited == lem->bfs_round", means node is already visited this round of bfs,,
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
			del_address_lst(open);
			printf("BFS LM_TRUE\n");
			return (LM_TRUE);
		}
		ret = iter_adja_of_current(*current, &open, lem->bfs_round);
		del_top_elem(&open);
	}
	del_address_lst(open);
	printf("BFS LM_FALSE, open [%p], ret[%d]\n", open, ret);

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

uint8_t				traversable_check(t_node *parent, t_node *child)
{
	t_path 		*p;
	t_node		*adjacen_node;

	p = parent->path_lst;
	adjacen_node = p->addr;
	while ( adjacen_node != child)
	{
		p = p->next;

		//=========== à supprimer
		if (p == NULL)
			printf("ERROR1 in traversable_check!!!!!!!!!!!!!\n");
		//=========== 


		adjacen_node = p->addr;
	}

	// ============. à supprimer
	if (p->flow != 0 && p->flow != 1)
			printf("ERROR2 in traversable_check!!!!!!!!!!!!!\n");
		// =============


	if (p->flow == 1)
	{
		printf("[%s] -> [%s] forbidden_path\n", parent->name, child->name);
		ft_lstadd_top(&(parent->forbidden_path), address_list_new(&child));
		return (LM_FALSE);
	}
	else
		return (LM_TRUE);
}

uint8_t		manage_cross_road(t_lemin *lem)
{
	t_node		*child;
	t_node		*parent;

	child = lem->end;
	while (child != lem->start)
	{
		parent = child->parent_addr;
		if (parent->node_flow > 0)
		{
			if (traversable_check(parent, child) == LM_FALSE)
			{
				return (LM_FALSE);
			}
		}
		child = parent;
	}
	return (LM_TRUE);
}

t_list			*get_pathway(t_lemin *lem)
{
	t_node		*child;
	t_list		*pathway;


	child = lem->end;
	ft_lstadd_top(&pathway, address_list_new(&child));
	while (child != lem->start)
	{
		child = child->parent_addr;
		ft_lstadd_top(&pathway, address_list_new(&child));
	}
	return (pathway);
}



/*
** wanted_flow is the maximum flow that we want,
** it will limite max_flow returned
** if lem->nb_ants < max_flow, then the flow returned is wanted_flow,
** else, the flow returned is the maximum flow that anthill can provide.
** but if wanted_flow == 0, it will return the actual maximum flow
** bfs_round represents how many times bfs has been lauched
*/

uint32_t			fulkerson_algo(t_lemin *lem,
									uint32_t wanted_flow)
{
	uint32_t	max_flow;
	t_list		*pathway;

	max_flow = 0;
	pathway = NULL;
	while (breadth_first_search(lem))
	{
		pathway = get_pathway(lem);
		debug_print_address_lst(pathway);

		if (manage_cross_road(lem))
		{
			modify_residual_graph(lem);
			max_flow++;
		}
		if (wanted_flow > 0 && max_flow == wanted_flow)
			return (wanted_flow);
	}
	return (max_flow);
}
