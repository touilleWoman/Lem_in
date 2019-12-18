/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_path_bis3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naali <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 14:39:38 by naali             #+#    #+#             */
/*   Updated: 2019/12/18 14:40:02 by naali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

/*
** Vide la liste et met
** a NULL le pointeur
*/

void					clear_path(t_path **start)
{
	t_path			*tmp;

	if (start != NULL && *start != NULL)
	{
		tmp = *start;
		while (tmp != NULL)
		{
			*start = tmp->next;
			free_path(&tmp);
			tmp = *start;
		}
	}
}

/*
** Echange les ids de 2 maillons
** sans changer les positions des noeuds
*/

void					swap_id_path(t_path *p1, t_path *p2)
{
	if (p1 != NULL && p2 != NULL)
		ft_swap((int*)&(p1->id), (int*)&(p2->id));
}
