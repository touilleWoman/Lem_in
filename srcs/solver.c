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

char			*get_occupied_node(t_node *enter)
{
	t_path		*p;

	p = enter->path_lst;
	while(p)
	{
		if (p->flow == 2)
		{
			// printf("Enter node[%s] to exit node[%s]\n",enter->name, p->name);
			return (p->name);
		}
		p = p->next;
	}
	return (NULL);
}

/*
** circuits are array of circuits found, array len = cir_nb
** value stored in array is address of poiter of t_node
*/

t_list		**retrace_circuits_from_graph(t_lemin *lem, uint32_t cir_nb)
{
	t_list			**circuits;
	uint32_t		i;
	t_node			*enter;
	t_node			*exit;
	char			*exit_name;

	i = 0;
	circuits = (t_list**)malloc(sizeof(t_list*) * cir_nb);
	if (!circuits)
		return (LM_FALSE);
	ft_bzero(circuits, cir_nb);
	while (i < cir_nb)
	{
		enter = lem->end;
		circuits[i] = address_list_new(&enter);
		while (enter != lem->start)
		{
			if ((exit_name = get_occupied_node(enter)) == NULL)
			{
				printf("exit_name == NULL\n");
				//free circuits ici !!
				return (NULL);
			}
			exit = get_node_in_hash(lem, exit_name);
			ft_lstadd_top(&(circuits[i]), address_list_new(&exit));
			flow_plus_modif(enter, exit, -1);
			flow_plus_modif(exit, enter, 1);
			enter = exit;
		}
		i++;
	}
	return (circuits);
}

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
** cir_nb[0] represents the number of circuits in cir_one,
** it's equal to nb of flow returned by fulkerson_algo().
** cir_nb[1] represents the number of circuits in cir_two.
** if lem->nb_ants % max_flow == 0, then cir_two is empty.
*/

void		solver(t_lemin *lem)
{
	int32_t			cir_nb[2];
	t_list			**cir_one;
	t_list			**cir_two;

	cir_two = NULL;
	cir_nb[0] = fulkerson_algo(lem, lem->nb_ants);
	cir_nb[1] = 0;
	cir_one = retrace_circuits_from_graph(lem, cir_nb[0]);
	if (lem->nb_ants % cir_nb[0] != 0)
	{
		cir_nb[1] = lem->nb_ants % cir_nb[0];
		fulkerson_algo(lem, cir_nb[1]);
		cir_two = retrace_circuits_from_graph(lem, cir_nb[1]);
	}
	// debug_print_circuits(cir_one, cir_nb[0]);
	// debug_print_circuits(cir_two, cir_nb[1]);
	print_ants(lem, cir_one, cir_two, cir_nb);
	free_circuits(cir_one, cir_nb[0]);
	free_circuits(cir_two, cir_nb[1]);

}



