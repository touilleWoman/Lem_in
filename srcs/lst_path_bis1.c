/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_path_bis1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naali <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 14:37:00 by naali             #+#    #+#             */
/*   Updated: 2019/12/18 15:07:01 by naali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

/*
** Met les id des noeuds
** a jour
*/

void					update_id_path(t_path **start)
{
	uint32_t		id;
	t_path			*tmp;

	id = 1;
	if (start != NULL && *start != NULL)
	{
		tmp = *start;
		while (tmp != NULL)
		{
			tmp->id = id++;
			tmp = tmp->next;
		}
	}
}

/*
** Cree un nouveau noeud
*/

t_path					*new_path(char *name, t_node *node)
{
	t_path			*path;
	static uint32_t	id = 0;

	if ((path = malloc(sizeof(t_path))) == NULL)
		return (NULL);
	id++;
	path->id = id;
	path->flow = 1;
	path->name = ft_strdup(name);
	path->addr = node;
	path->next = NULL;
	return (path);
}

/*
** Place un noeud
** en fin de liste
*/

void					pushback_path(t_path **start, t_path *node)
{
	t_path			*tmp;

	if (start != NULL && *start != NULL && node != NULL)
	{
		tmp = get_last_path(start);
		tmp->next = node;
	}
	else if (start != NULL && *start == NULL)
		*start = node;
}

/*
** Place un noeud
** en debut de liste
*/

void					pushfront_path(t_path **start, t_path *node)
{
	if (start != NULL && node != NULL)
	{
		node->next = *start;
		*start = node;
	}
}

/*
** Place le noeud apres le noeud
** avec l'id passe en parametre
*/

void					pushafter_path(t_path **start, uint32_t id,
										t_path *node)
{
	t_path			*tmp;

	if (start != NULL && *start != NULL && node != NULL)
	{
		tmp = *start;
		while (tmp != NULL && tmp->id != id)
			tmp = tmp->next;
		if (tmp != NULL && tmp->id == id)
		{
			node->next = tmp->next;
			tmp->next = node;
			while (tmp != NULL)
			{
				tmp->id = id++;
				tmp = tmp->next;
			}
		}
		else
			pushback_path(start, node);
		update_id_path(start);
	}
}
