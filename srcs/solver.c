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


uint8_t		not_visited(t_list *visited, t_path *p)
{
	while (visited != NULL)
	{
		if (p == (t_path*)visited)
			return (LM_FALSE);
		visited = visited->next;
	}
	return (LM_TRUE);
}

t_list		*node_list_new(t_node **new)
{
	t_list *lst;

	lst = ft_lstnew((void const *)new, sizeof(t_node*));
	return (lst);
}

void		iter_paths(t_path *p, t_list **visited, t_list **open, t_lemin *lem)
{
	t_node		*adjacen_node;

	while (p)
	{
		if (p->flow > 0 && not_visited(*visited, p))
		{
			adjacen_node = get_node_in_hash(lem, p->name);
			ft_lstadd_bot(visited, node_list_new(&adjacen_node));
			ft_lstadd_bot(open, node_list_new(&adjacen_node));
		}
		p = p->next;
	}
}


t_node		**pop_top_elem(t_list **alst)
{
	t_node	**ret;

	ret = NULL;
	if (alst != NULL && *alst != NULL)
	{
		ret = (t_node**)((*alst)->content);
		*alst = (*alst)->next;
	}
	return (ret);
}


uint8_t		breadth_first_search(t_lemin *lem)
{
	t_list	*open;
	t_list	*visited;
	t_node	*start;
	t_node	*end;
	t_node	**current;

	open = NULL;
	visited = NULL;
	current = NULL;
	start = get_node_in_hash(lem, lem->start);
	end = get_node_in_hash(lem, lem->end);
	open = node_list_new(&start);
	// printf("|unid[%d] ==> %s (nb_paths:%d)|\n", (*tmp)->unid, (*tmp)->name,
	// 		 (*tmp)->nb_paths);
	visited = node_list_new(&start);
	while (open != NULL)
	{
		current = pop_top_elem(&open);
		printf("current : unid[%d] ==> %s (nb_paths:%d)|\n", (*current)->unid, (*current)->name,
				 (*current)->nb_paths);
		ft_lstadd_bot(&visited, node_list_new(current));
		if (*current == end)
			return (LM_TRUE);
		// print_pth(&(current->path_lst));
		iter_paths((*current)->path_lst, &visited, &open, lem);
		//free current
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
