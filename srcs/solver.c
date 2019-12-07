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

int8_t			flow_plus_modif(t_node *enter, t_node *exit, int8_t modif)
{
	t_path	*p;

	p = enter->path_lst;
	while(p)
	{
		if (ft_strcmp(p->name, exit->name) == 0)
		{
			p->flow += modif;
			return (LM_SUCCESS);
		}
		p = p->next;
	}
	return (LM_ERROR);
}

static t_circuits		**init_cir_tab(uint32_t tab_len)
{
	t_circuits		**cir_tab;
	uint32_t		i;

	i = 0;
	cir_tab = (t_circuits**)malloc(sizeof(t_circuits*) * tab_len);
	if (!cir_tab)
		return (NULL);
	while (i < tab_len)
	{
		cir_tab[i] = (t_circuits*)malloc(sizeof(t_circuits));
		if (!cir_tab[i])
		{
			free_cir_tab(cir_tab, tab_len);
			return (NULL);
		}
		cir_tab[i]->addr = NULL;
		cir_tab[i]->nb_floor = 0;
		i++;
	}
	return (cir_tab);
}

void		solver(t_lemin *lem)
{
	int32_t			tab_len;
	t_circuits		**cir_tab;

	tab_len = fulkerson_algo(lem, lem->nb_ants);
	if (tab_len == 0)
		return ;
	cir_tab = init_cir_tab(tab_len);
	if (!cir_tab)
		return ;
	if (retrace_circuits(lem, tab_len, cir_tab))
	{
		debug_print_circuits(cir_tab, tab_len);
		print_ants(lem, cir_tab, tab_len);
	}
	free_cir_tab(cir_tab, tab_len);
}
