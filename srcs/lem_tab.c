/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_tab.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabih <naali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 23:19:25 by nabih             #+#    #+#             */
/*   Updated: 2019/11/23 03:57:25 by nabih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

/*
** Ajoute un element
** au tableau de hash
*/
void					add_node_in_tab(t_lemin *lem, t_node *node)
{
	if (node != NULL && node->id < HASHCODE)
		pushfront_node(&(lem->tab[node->id]), node);
}

/*
** Vide le tableau
** et free les espaces
*/
void					clear_hashtab(t_lemin *lem)
{
	uint32_t		i;

	i = 0;
	while (i < HASHCODE)
	{
		if ((lem->tab)[i] != NULL)
			clear_node(&((lem->tab)[i]));
		i++;
	}
}

/*
** Verifie si un noeud exite deja
** retourne vrai ou faux
*/
uint8_t					node_exist(t_lemin *lem, char *name)
{
	t_node			*tmp;

	if (lem != NULL && name != NULL)
	{
		tmp = (lem->tab)[hash_name(name)];
		while (tmp != NULL)
		{
			if (ft_strcmp(tmp->name, name) == 0)
				return (LM_TRUE);
			tmp = tmp->next;
		}
	}
	return (LM_FALSE);
}
