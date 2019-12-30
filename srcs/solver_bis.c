/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver_bis.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naali <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 15:10:17 by naali             #+#    #+#             */
/*   Updated: 2019/12/18 15:12:00 by naali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solver.h"

int8_t			flow_plus_modif(t_node *enter, t_node *exit,
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

void			free_cir_tab(t_circuits **cir_tab, uint32_t tab_len)
{
	uint32_t	i;

	i = 0;
	if (cir_tab)
	{
		while (i < tab_len)
		{
			if (cir_tab[i])
			{
				del_address_lst(&(cir_tab[i]->addr));
				free(cir_tab[i]);
				cir_tab[i] = NULL;
			}
			i++;
		}
		free(cir_tab);
		cir_tab = NULL;
	}
}
