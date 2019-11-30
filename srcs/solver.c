/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleblond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 17:25:51 by jleblond          #+#    #+#             */
/*   Updated: 2019/11/29 17:25:54 by jleblond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solver.h"

void		iter_adja_of_current(t_node *current, t_list **visited, t_list **open, t_lemin *lem)
{
	t_node		*adjacen_node;
	t_path		*p;

	p = current->path_lst;
	while (p)
	{
		adjacen_node = get_node_in_hash(lem, p->name);
		if (p->flow > 0 && not_in_address_lst(*visited, adjacen_node))
		{
			ft_lstadd_bot(visited, address_list_new(&adjacen_node));
			ft_lstadd_bot(open, address_list_new(&adjacen_node));
			adjacen_node->parent_name = (current->name);
		}
		p = p->next;
	}
}

t_node		**get_top_elem(t_list *lst)
{
	t_node	**ret;

	ret = NULL;
	if (lst != NULL)
	{
		ret = (t_node**)(lst->content);
	}
	return (ret);
}

/*
** here, t_list store addree of pointer of node in lst->content
** "open" are nodes to be evaluate, elements are always added to the end,
** and taken from the top to be evaluated. Delete top elem after evaluation.
** "visited" are nodes already visited, if inside, we don't evaluate this node
*/

uint8_t		breadth_first_search(t_lemin *lem)
{
	t_list	*open;
	t_list	*visited;
	t_node	**current;

	visited = NULL;
	open = address_list_new(&(lem->start));
	while (open != NULL)
	{
		current = get_top_elem(open);
		// printf("debug open start\n");
		// debug_print_address_lst(&open);
		// printf("debug end\n");
		// printf("debug visited start\n");
		// debug_print_address_lst(&visited);
		// printf("debug end\n");
		if (not_in_address_lst(visited, *current))
			ft_lstadd_bot(&visited, address_list_new(current));
		if (*current == lem->end)
		{
			del_address_lst(visited);
			del_address_lst(open);
			return (LM_TRUE);
		}
		iter_adja_of_current(*current, &visited, &open, lem);
		del_first_elem(&open);
	}
	del_address_lst(visited);
	del_address_lst(open);
	return (LM_FALSE);
}

int8_t			modify_flow(t_node *parent, t_node *child, int flow)
{
	t_path	*p;

	p = parent->path_lst;
	while(p)
	{
		if (ft_strcmp(p->name, child->name) == 0)
		{
			// printf("flow of pathname[%s] changed from [%d] to [%d]\n", p->name, p->flow, flow);
			p->flow = flow;
			return (LM_SUCCESS);
		}
		p = p->next;
	}
	return (LM_ERROR);
}

uint32_t		fulkerson_algo(t_lemin *lem)
{
	uint32_t	max_flow;
	t_node		*parent;
	t_node		*child;

	max_flow = 0;
	while (breadth_first_search(lem))
	{
		printf("BFS lauched, max_flow = [%d]\n", max_flow);
		max_flow++;
		child = lem->end;
		while (child != lem->start)
		{
			printf("parent name%s\n", (child->parent_name));
			parent = get_node_in_hash(lem, child->parent_name);
			modify_flow(parent, child, 0);
			modify_flow(child, parent, 2);
			child = parent;
		}
	}
	return (max_flow);
}

void		solver(t_lemin *lem)
{
	uint32_t	max_flow;

	max_flow = fulkerson_algo(lem);
	printf("fulkerson_algo done, max_flow=%d\n", max_flow);
}
