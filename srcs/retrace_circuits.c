/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   retrace_circuits.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleblond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 13:34:02 by jleblond          #+#    #+#             */
/*   Updated: 2020/01/02 11:46:53 by jleblond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solver.h"

static t_node			*get_parent(t_node *enter)
{
	t_path		*p;

	p = enter->path_lst;
	while (p)
	{
		if (p->flow == 2)
			return (p->addr);
		p = p->next;
	}
	return (NULL);
}

static uint8_t			retrace_one_and_reset_flow(t_lemin *lem,
													t_circuits *cir)
{
	t_node			*child;
	t_node			*parent;
	uint32_t		nb_floor;
	t_list			*new;

	child = lem->end;
	nb_floor = 0;
	while (child != lem->start)
	{
		parent = get_parent(child);
		if (!parent)
			return (LM_FALSE);
		new = address_list_new(&parent);
		if (!new)
			return (LM_FALSE);
		ft_lstadd_top(&(cir->addr), new);
		flow_plus_modif(child, parent, -1);
		flow_plus_modif(parent, child, 1);
		child = parent;
		nb_floor++;
	}
	cir->nb_floor = nb_floor;
	return (LM_TRUE);
}

static void				sort_path(t_circuits **c, uint32_t len)
{
	uint32_t		i;
	uint32_t		j;

	i = 0;
	while (i < len)
	{
		j = len - 1;
		while (j > i)
		{
			if (c[i]->nb_floor > c[j]->nb_floor)
				ft_swap_ptr((void**)&(c[i]), (void**)&(c[j]));
			--j;
		}
		++i;
	}
}

static t_circuits		**init_cir_tab(uint32_t tab_len)
{
	t_circuits		**cir_tab;
	uint32_t		i;

	i = 0;
	if ((cir_tab = (t_circuits**)malloc(sizeof(t_circuits*) * tab_len)) == NULL)
		return (NULL);
	while (i < tab_len)
	{
		if ((cir_tab[i] = (t_circuits*)malloc(sizeof(t_circuits))) == NULL)
		{
			free_cir_tab(cir_tab, tab_len);
			return (NULL);
		}
		ft_bzero(cir_tab[i], sizeof(t_circuits));
		i++;
	}
	return (cir_tab);
}

/*
** circuits are array of t_circuits, array len = tab_len.
** t_circuits contains : (uint32_t)nb_floor, (t_list)*addr;
** nb_floor is nb of nodes in each circuit.
** adddr is list of address of node
*/

t_circuits				**retrace_circuits(t_lemin *lem, uint32_t tab_len)
{
	uint32_t		i;
	t_circuits		**cir_tab;

	cir_tab = init_cir_tab(tab_len);
	if (!cir_tab)
		return (NULL);
	i = 0;
	while (i < tab_len)
	{
		cir_tab[i]->addr = address_list_new(&(lem->end));
		if (cir_tab[i]->addr == NULL)
			break ;
		if (retrace_one_and_reset_flow(lem, cir_tab[i]) == LM_FALSE)
			break ;
		i++;
	}
	if (i == tab_len)
		sort_path(cir_tab, tab_len);
	else
	{
		free_cir_tab(cir_tab, tab_len);
		cir_tab = NULL;
	}
	return (cir_tab);
}
