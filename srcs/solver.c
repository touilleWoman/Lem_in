/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleblond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 17:25:51 by jleblond          #+#    #+#             */
/*   Updated: 2019/12/08 08:07:24 by nabih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solver.h"

int8_t					flow_plus_modif(t_node *enter, t_node *exit,
										int8_t modif)
{
	t_path			*p;

	p = enter->path_lst;
	while (p)
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

void					solver(t_lemin *lem)
{
	int32_t			tab_len;
	t_circuits		**cir_tab;

	clock_t	start_t, finish_t;

	start_t = clock();
	printf("start algo time%ld\n", start_t);
	if ((tab_len = fulkerson_algo(lem, lem->nb_ants)) == 0)
		return ;
	cir_tab = init_cir_tab(tab_len);
	if ((cir_tab = init_cir_tab(tab_len)) == NULL)
		return ;
	if (retrace_circuits(lem, tab_len, cir_tab))
	{
		finish_t = clock();
		printf("finish algo time%ld\n", finish_t);

		// debug_print_circuits(cir_tab, tab_len);
		print_ants(lem, cir_tab, tab_len);
	}
	free_cir_tab(cir_tab, tab_len);
}
