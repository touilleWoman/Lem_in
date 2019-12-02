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
		del_top_elem(&open);
	}
	del_address_lst(visited);
	del_address_lst(open);
	return (LM_FALSE);
}

int8_t			flow_plus_modif(t_node *enter, t_node *exit, int8_t modif)
{
	t_path	*p;

	p = enter->path_lst;
	while(p)
	{
		if (ft_strcmp(p->name, exit->name) == 0)
		{
			// printf("flow of pathname[%s] changed from [%d] to [%d]\n", p->name, p->flow, modif);
			p->flow += modif;
			return (LM_SUCCESS);
		}
		p = p->next;
	}
	return (LM_ERROR);
}

char			*get_occupied_node(t_node *enter)
{
	t_path		*p;

	p = enter->path_lst;
	while(p)
	{
		if (p->flow == 2)
		{
			printf("Enter node[%s] to exit node[%s]\n",enter->name, p->name);
			return (p->name);
		}
		p = p->next;
	}
	return (NULL);
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
			flow_plus_modif(parent, child, -1);
			flow_plus_modif(child, parent, 1);
			child = parent;
		}
	}
	return (max_flow);
}

uint8_t		retrace_circuits_from_graph(t_lemin *lem, uint32_t nb_p)
{
	t_list			**circuits;
	uint32_t		i;
	t_node			*enter;
	t_node			*exit;
	char			*exit_name;

	i = 0;
	circuits = (t_list**)malloc(sizeof(t_list*) * nb_p);
	if (!circuits)
		return (LM_FALSE);
	while (i < nb_p)
	{
		printf("Path No [%d]\n",i);
		enter = lem->end;
		circuits[i] = address_list_new(&enter);
		while (enter != lem->start)
		{
			if ((exit_name = get_occupied_node(enter)) == NULL)
			{
				printf("exit_name == NULL\n");
				return (LM_FALSE);
			}
			exit = get_node_in_hash(lem, exit_name);
			ft_lstadd_top(&(circuits[i]), address_list_new(&exit));
			flow_plus_modif(enter, exit, -1);
			flow_plus_modif(exit, enter, +1);
			enter = exit;
		}
		i++;
	}
	return (LM_TRUE);
}

void		solver(t_lemin *lem)
{
	uint32_t	max_flow;

	max_flow = fulkerson_algo(lem);
	printf("fulkerson_algo done, max_flow=%d\n", max_flow);
	print_tab(lem->tab, HASHCODE);
	retrace_circuits_from_graph(lem, max_flow);
	printf("after retrac\n");
	print_tab(lem->tab, HASHCODE);


}
