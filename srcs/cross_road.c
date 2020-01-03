/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cross_road.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleblond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/02 11:50:07 by jleblond          #+#    #+#             */
/*   Updated: 2020/01/03 10:15:00 by naali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solver.h"

static uint8_t			get_flow_node1_to_node2(t_node *node1, t_node *node2)
{
	t_path		*p;

	p = node1->path_lst;
	while (p->addr != node2)
		p = p->next;
	return (p->flow);
}

t_list					*get_pathway(t_lemin *lem)
{
	t_node		*child;
	t_list		*pathway;

	pathway = NULL;
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
** if path_flow == 2, means this step in precedent circuit will be canceled
** by modifying path flow later.
** To update node_flow, We should reduce node_flow by 1 (node_flow -= 1)
** but still need check that its node_flow == 1,
** because this node could have been canceled twice when passed by two circutis
*/

void					pathway_node_flow_update(t_list *lst)
{
	t_node		*node1;
	t_node		*node2;
	uint8_t		path_flow;

	while (lst && lst->next)
	{
		node1 = *(t_node**)(lst->content);
		node2 = *(t_node**)(lst->next->content);
		path_flow = get_flow_node1_to_node2(node1, node2);
		if (path_flow == 2)
		{
			node1->node_flow == 1 ? node1->node_flow -= 1 : 0;
			node2->node_flow == 1 ? node2->node_flow -= 1 : 0;
		}
		lst = lst->next;
	}
}

static void				forbade_next_step(t_list *lst)
{
	t_node		*node1;
	t_node		*node2;

	node1 = *(t_node**)(lst->content);
	node2 = *(t_node**)(lst->next->content);
	ft_lstadd_top(&(node1->forbidden_path), address_list_new(&node2));
}

uint8_t					cross_road_ok(t_list *lst, t_lemin *lem)
{
	t_node		*node2;

	while (lst && lst->next)
	{
		node2 = *(t_node**)(lst->next->content);
		if (node2 != lem->end && node2->node_flow > 0)
		{
			forbade_next_step(lst->next);
			return (LM_FALSE);
		}
		lst = lst->next;
	}
	return (LM_TRUE);
}
