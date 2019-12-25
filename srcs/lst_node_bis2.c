/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_node_bis2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naali <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 14:25:30 by naali             #+#    #+#             */
/*   Updated: 2019/12/18 15:05:37 by naali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

/*
** Compte le nombre de
** noeud dans la liste
*/

uint32_t				count_node(const t_node *start)
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

t_node					*get_last_node(t_node **start)
{
	t_node			*tmp;

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
** avec le nom passe en parametre
*/

t_node					*get_node_by_name(t_node **start, char *name)
{
	t_node			*tmp;

	tmp = NULL;
	if (start != NULL && *start != NULL && name != NULL)
	{
		tmp = *start;
		while (tmp != NULL && ft_strcmp(tmp->name, name) != 0)
			tmp = tmp->next;
	}
	return (tmp);
}

/*
** Free 1 noeud
*/

void					free_node(t_node **node)
{
	ft_memdel((void**)&((*node)->name));
	clear_path(&((*node)->path_lst));
	del_address_lst(&((*node)->forbidden_path));
	ft_memdel((void**)node);
}
