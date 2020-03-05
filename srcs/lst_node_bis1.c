/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_node_bis1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naali <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 14:23:13 by naali             #+#    #+#             */
/*   Updated: 2020/01/03 15:30:30 by naali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

/*
** Cree un nouveau noeud
*/

t_node					*new_node(char *name)
{
	int32_t			id;
	t_node			*node;

	if ((node = malloc(sizeof(t_node))) == NULL)
		return (NULL);
	if ((id = hash_name(name)) == LM_ERROR || id >= HASHCODE)
	{
		free(node);
		return (NULL);
	}
	node->id = id;
	node->name = ft_strdup(name);
	node->parent_addr = NULL;
	node->nb_paths = 0;
	node->path_lst = NULL;
	node->next = NULL;
	node->visited = 0;
	node->node_flow = 0;
	node->forbidden_path = NULL;
	return (node);
}

/*
** Place un noeud
** en fin de liste
*/

void					pushback_node(t_node **start, t_node *node)
{
	t_node			*tmp;

	if (start != NULL && *start != NULL && node != NULL)
	{
		tmp = get_last_node(start);
		tmp->next = node;
	}
	else if (start != NULL && *start == NULL)
		*start = node;
}

/*
** Place un noeud
** en debut de liste
*/

void					pushfront_node(t_node **start, t_node *node)
{
	if (start != NULL && node != NULL)
	{
		node->next = *start;
		*start = node;
	}
}

/*
** Place le noeud apres le noeud
** avec le nom passe en parametre
*/

void					pushafter_node(t_node **start, char *name, t_node *node)
{
	t_node			*tmp;

	if (start != NULL && *start != NULL && node != NULL && name != NULL)
	{
		tmp = *start;
		while (tmp != NULL && ft_strcmp(tmp->name, name) != 0)
			tmp = tmp->next;
		if (tmp != NULL)
		{
			node->next = tmp->next;
			tmp->next = node;
		}
	}
}
