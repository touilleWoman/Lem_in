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

t_circuits				**init_cir_tab(uint32_t tab_len)
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

void					del_longer_cir(t_circuits **c1, t_circuits **c2)
{
	if ((*c1)->nb_floor < (*c2)->nb_floor)
		ft_memdel((void**)c2);
	else
		ft_memdel((void**)c1);
}

void					looking_for_duplicated_node(t_circuits **c, uint32_t i,
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
				del_longer_cir(&(c[i]), &(c[j]));
				return ;
			}
			lst2 = lst2->next;
		}
		lst1 = lst1->next;
	}
}
