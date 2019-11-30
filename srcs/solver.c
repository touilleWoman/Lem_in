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


void		iter_adja_of_current(t_path *p, t_list **visited, t_list **open, t_lemin *lem)
{
	t_node		*adjacen_node;

	while (p)
	{
		adjacen_node = get_node_in_hash(lem, p->name);
		// printf("visited list:\n");
		if (p->flow > 0 && not_in_address_lst(*visited, adjacen_node))
		{
			ft_lstadd_bot(visited, address_list_new(&adjacen_node));
			ft_lstadd_bot(open, address_list_new(&adjacen_node));
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

	open = address_list_new(&(lem->start));
	while (open != NULL)
	{
		current = get_top_elem(open);
		if (not_in_address_lst(visited, *current))
			ft_lstadd_bot(&visited, address_list_new(current));
		if (*current == lem->end)
			return (LM_TRUE);
		iter_adja_of_current((*current)->path_lst, &visited, &open, lem);
		del_first_elem(&open);

	}
	return (LM_FALSE);
}


void		fulkerson_algo(t_lemin *lem)
{

	if (breadth_first_search(lem))
		printf("chemin trouvé!\n");
	else
		printf("pas de chemin!\n");

}

void		solver(t_lemin *lem)
{
	fulkerson_algo(lem);
}
