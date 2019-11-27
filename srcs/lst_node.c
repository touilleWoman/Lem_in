/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_node.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabih <naali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 20:50:08 by nabih             #+#    #+#             */
/*   Updated: 2019/11/27 16:57:31 by nabih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

/*
** Cree un nouveau noeud
*/
t_node					*new_node(char *name, uint8_t start, uint8_t end)
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
	node->dist = 0;
	node->nb_paths = 0;
	node->start = start;
	node->end = end;
	node->path_lst = NULL;
	node->next = NULL;
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
static void				free_node(t_node **node)
{
	ft_memdel((void**)&((*node)->name));
	clear_path(&((*node)->path_lst));
	ft_memdel((void**)node);
}

/*
** Detruit le noeud
** en fonction du nom
*/
void					del_node(t_node **start, char *name)
{
	t_node			*tmp1;
	t_node			*tmp2;

	if (start != NULL && *start != NULL && name != NULL)
	{
		tmp1 = *start;
		if (ft_strcmp(tmp1->name, name) == 0)
		{
			*start = tmp1->next;
			free_node(&tmp1);
		}
		else
		{
			while (tmp1->next != NULL && ft_strcmp(tmp1->next->name, name) != 0)
				tmp1 = tmp1->next;
			if (tmp1->next != NULL && ft_strcmp(tmp1->next->name, name) == 0)
			{
				tmp2 = tmp1->next;
				tmp1->next = tmp1->next->next;
				free_node(&tmp2);
			}
		}
	}
}

/*
** Vide la liste et met
** a NULL le pointeur
*/
void					clear_node(t_node **start)
{
	t_node			*tmp;

	if (start != NULL && *start != NULL)
	{
		tmp = *start;
		while (tmp != NULL)
		{
			*start = tmp->next;
			free_node(&tmp);
			tmp = *start;
		}
	}
}

/*
** Retire le noeud avec le nom passe en parametre de la liste
** elle ne le detruit pas mais renvoi un pointeur sur lui.
*/
static t_node			*remov_first_node(t_node **start)
{
	t_node			*ret;

	ret = *start;
	*start = ret->next;
	ret->next = NULL;
	return (ret);
}

t_node					*remove_from_node(t_node **start, char *name)
{
	t_node			*tmp;
	t_node			*ret;

	ret = NULL;
	if (start != NULL && *start != NULL && name != NULL)
	{
		tmp = *start;
		if (ft_strcmp(tmp->name, name) == 0)
			ret = remov_first_node(start);
		else
		{
			while (tmp->next != NULL && ft_strcmp(tmp->next->name, name) != 0)
				tmp = tmp->next;
			if (tmp->next != NULL)
			{
				ret = tmp->next;
				tmp->next = ret->next;
				ret->next = NULL;
			}
		}
	}
	return (ret);
}

/*
** Transfert un noeud d'une liste
** a une autre liste
*/
void					send_node_away(t_node **src, t_node **dst, char *name)
{
	t_node			*tmp;

	if (src != NULL && *src != NULL && dst != NULL && name != NULL)
	{
		tmp = remove_from_node(src, name);
		pushback_node(dst, tmp);
	}
}
