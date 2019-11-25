/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabih <naali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 13:50:24 by nabih             #+#    #+#             */
/*   Updated: 2019/11/25 21:26:47 by nabih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <solver.h>

static void				init_flow(t_lemin *lem, t_flow *f)
{
	t_node			*tmp;

	f->now = 0;
	tmp = get_node_in_hash(lem, lem->start);
	f->start = tmp->nb_paths;
	tmp = get_node_in_hash(lem, lem->end);
	f->end = tmp->nb_paths;
	f->max = (f->start <= f->end) ? f->start : f->end;
}

uint8_t					check_links(t_lemin *lem, uint32_t indice, char *name)
{
	t_path			*tmp;

	tmp = lem->pth[indice];
	while (tmp != NULL)
	{
		lem->dash = tmp->id;
		if (ft_strcmp(tmp->name[0], name))
			return (LM_TRUE);
		else if (ft_strcmp(tmp->name[1], name))
			return (LM_TRUE);
		tmp = tmp->next;
	}
	return (LM_FALSE);
}

int8_t					solver(t_lemin *lem)
{
	t_flow			f;

	init_flow(lem, &f);
	return (LM_SUCCESS);
}

/*
  	   START
  	 ___/|
   /	 |
  2		 1 ---- 5
  |		 |      |
  |		 |	    |
  4 ---- 3		6
         |	___/
   		 |/
		END
*/
