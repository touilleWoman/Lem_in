/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleblond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 17:25:51 by jleblond          #+#    #+#             */
/*   Updated: 2019/12/16 17:22:16 by nabih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solver.h"
#include "get_many_path.h"

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

static void				looking_for_duplicated_node(t_circuits **c, uint32_t i,
													uint32_t j)
{
	t_list			*lst1;
	t_list			*lst2;
	t_node			*n1;
	t_node			*n2;

	if (!(c[i]) || !(c[j]))
		return ;
	lst1 = c[i]->addr;
	while (lst1->next)
	{
		n1 = *(t_node**)lst1->content;
		lst2 = ((t_list*)c[j]->addr)->next;
		while (lst2->next)
		{
			n2 = *(t_node**)lst2->content;
			if (ft_strcmp(n1->name, n2->name) == 0)
			{
				if (c[i]->nb_floor < c[j]->nb_floor)
					ft_memdel((void**)&(c[j]));
				else
					ft_memdel((void**)&(c[i]));
				return ;
			}
			lst2 = lst2->next;
		}
		lst1 = lst1->next;
	}
}

static uint32_t			remove_null(t_circuits **c, uint32_t len)
{
	uint32_t		i;
	uint32_t		j;

	i = 0;
	while (i < len)
	{
		if (!(c[i]))
		{
			j = i + 1;
			while (j < len && !(c[i]))
			{
				ft_swap_ptr((void**)&(c[i]), (void**)&(c[j]));
				++j;
			}
		}
		++i;
	}
	i = 0;
	while (i < len && c[i])
		i++;
	return (i);
}

static uint32_t			duplicate_check(t_circuits **c, uint32_t len)
{
	uint32_t		i;
	uint32_t		j;

	i = 0;
	while (i < len)
	{
		j = len - 1;
		while (j > i)
		{
			looking_for_duplicated_node(c, i, j);
			--j;
		}
		++i;
	}
	return (remove_null(c, len));
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

uint32_t				choose_wanted_flow(t_lemin *lem)
{
	uint32_t		wanted_flow;

	if (lem->start->nb_paths > lem->end->nb_paths)
		wanted_flow = lem->end->nb_paths;
	else
		wanted_flow = lem->end->nb_paths;
	if ((uint32_t)lem->nb_ants < wanted_flow)
		wanted_flow = (uint32_t)lem->nb_ants;
	return (wanted_flow);
}

// decommente pour voir le temps utilisé
void					solver(t_lemin *lem)
{
	uint32_t		wanted_flow;
	int32_t			tab_len;
	t_circuits		**cir_tab;
	t_list			*ants;

	/* clock_t	start_t, finish_t; */
	/* start_t = clock(); */
	wanted_flow = choose_wanted_flow(lem);
	if ((tab_len = fulkerson_algo(lem, wanted_flow)) == 0)
		return ;
	if ((cir_tab = init_cir_tab(tab_len)) == NULL)
		return ;

	/* finish_t = clock() - start_t; */
	/* printf("fulkerson_algo time%f\n", (double)finish_t / CLOCKS_PER_SEC); */
	/* start_t = clock(); */

	if (retrace_circuits(lem, tab_len, cir_tab))
	{
		/* finish_t = clock() - start_t; */
		/* printf("retrace_circuits time%f\n", (double)finish_t / CLOCKS_PER_SEC); */
		/* start_t = clock(); */

		tab_len = duplicate_check(cir_tab, tab_len);
		sort_path(cir_tab, tab_len);
//		app_max = get_appro_max(cir_tab, tab_len, lem->nb_ants);// Calcul approximatif du nombre de ligne
		ants = init_ant_lst(lem->nb_ants);

		/* finish_t = clock() - start_t; */
		/* printf("sort+antlst time%f\n", (double)finish_t / CLOCKS_PER_SEC); */
		/* start_t = clock(); */

//		debug_print_circuits(cir_tab, tab_len);
		print_ants(lem, &ants, cir_tab, tab_len);

		/* finish_t = clock() - start_t; */
		/* printf("print path time%f\n", (double)finish_t / CLOCKS_PER_SEC); */
	}
	free_cir_tab(cir_tab, tab_len);
}
