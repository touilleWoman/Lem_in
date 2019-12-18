/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_path_bis2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naali <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 14:38:21 by naali             #+#    #+#             */
/*   Updated: 2019/12/18 15:07:44 by naali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

/*
** Compte le nombre de
** noeud dans la liste
*/

uint32_t				count_path(const t_path *start)
{
	uint32_t		nb;

	nb = 0;
	while (start != NULL)
	{
		start = start->next;
		nb++;
	}
	return (nb);
}

/*
** Renvoi le dernier
** noeud de la liste
*/

t_path					*get_last_path(t_path **start)
{
	t_path			*tmp;

	tmp = NULL;
	if (start != NULL && *start != NULL)
	{
		tmp = *start;
		while (tmp->next != NULL)
			tmp = tmp->next;
	}
	return (tmp);
}

/*
** Renvoi un pointeur sur le noeud
** avec l'id passe en parametre
*/

t_path					*get_path_by_id(t_path **start, uint32_t id)
{
	t_path			*tmp;

	tmp = NULL;
	if (start != NULL && *start != NULL)
	{
		tmp = *start;
		while (tmp != NULL && tmp->id != id)
			tmp = tmp->next;
	}
	return (tmp);
}

/*
** Free path
*/

void					free_path(t_path **path)
{
	t_path			*tmp;

	tmp = *path;
	if (tmp != NULL)
	{
		ft_memdel((void**)&(tmp->name));
		ft_memdel((void**)&tmp);
		*path = NULL;
	}
}

/*
** Detruit le noeud
** en fonction de l'id
*/

void					del_path(t_path **start, uint32_t id)
{
	t_path			*tmp1;
	t_path			*tmp2;

	if (start != NULL && *start != NULL && id > 0)
	{
		tmp1 = *start;
		if (tmp1->id == id)
		{
			*start = tmp1->next;
			free_path(&tmp1);
		}
		else
		{
			while (tmp1->next != NULL && tmp1->next->id != id)
				tmp1 = tmp1->next;
			if (tmp1->next != NULL && tmp1->next->id == id)
			{
				tmp2 = tmp1->next;
				tmp1->next = tmp1->next->next;
				free_path(&tmp2);
			}
		}
		update_id_path(start);
	}
}
