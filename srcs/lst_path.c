/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naali <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 09:24:18 by naali             #+#    #+#             */
/*   Updated: 2019/11/29 20:38:43 by nabih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

/*
** Met les id des noeuds
** a jour
*/
static void				update_id_path(t_path **start)
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
t_path					*new_path(uint32_t unid, char *name)
{
	t_path			*path;
	static uint32_t	id = 0;

	if ((path = malloc(sizeof(t_path))) == NULL)
		return (NULL);
	id++;
	path->id = id;
	path->flow = 1;
	path->name = ft_strdup(name);
	path->unid = unid;
	path->next = NULL;
	return (path);
}

// t_path					*copy_path(const t_path *pth)
// {
// 	t_path			*path;

// 	if ((path = malloc(sizeof(t_path))) == NULL)
// 		return (NULL);
// 	ft_memcpy((void*)path, (void*)(pth), sizeof(t_path));
// 	path->name[0] = ft_strdup(path->name[0]);
// 	path->name[1] = ft_strdup(path->name[1]);
// 	return (path);
// }

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
	// uint32_t		id;

	if (start != NULL && node != NULL)
	{
		// id = 1;
		node->next = *start;
		*start = node;
		// update_id_path(start);
	}
}

/*
** Place le noeud apres le noeud
** avec l'id passe en parametre
*/
void					pushafter_path(t_path **start, uint32_t id, t_path *node)
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
static void				free_path(t_path **path)
{
	t_path			*tmp;

	tmp = *path;
	if (tmp != NULL)
	{
		ft_memdel((void**)&(tmp->name));
		// ft_memdel((void**)&(tmp->name[0]));
		// ft_memdel((void**)&(tmp->name[1]));
		ft_memdel((void**)&tmp);
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

/*
** Retire le noeud avec l'id passe en parametre de la liste
** elle ne le detruit pas mais renvoi un pointeur sur lui.
*/
static t_path			*remov_first_path(t_path **start)
{
	t_path			*ret;

	ret = *start;
	*start = ret->next;
	ret->next = NULL;
	return (ret);
}

static t_path			*remov_last_path(t_path **start)
{
	t_path			*tmp;
	t_path			*ret;

	ret = get_last_path(start);
	tmp = get_path_by_id(start, ret->id - 1);
	tmp->next = NULL;
	return (ret);
}

t_path					*remove_from_path(t_path **start, uint32_t id,\
											uint8_t flag)
{
	t_path			*tmp;
	t_path			*ret;

	ret = NULL;
	if (start != NULL && *start != NULL)
	{
		if (id > 1 && id < count_path(*start))
		{
			tmp = get_path_by_id(start, (id - 1));
			ret = tmp->next;
			tmp->next = ret->next;
			ret->next = NULL;
		}
		else if (id == 1 || id == count_path(*start))
			ret = (id == 1) ? remov_first_path(start) : remov_last_path(start);
		(flag == LM_TRUE) ? update_id_path(start) : 0;
	}
	return (ret);
}

/*
** Echange les positions de
** deux noeuds
*/
void					swap_path_by_id(t_path **start, uint32_t id1, uint32_t id2)
{
	t_path			*tmp1;
	t_path			*tmp2;

	if ((id1 >= 1 && id1 <= count_path(*start))\
		&& (id1 >= 1 && id1 <= count_path(*start)))
	{
		tmp1 = remove_from_path(start, id1, LM_FALSE);
		tmp2 = remove_from_path(start, id2, LM_FALSE);
		if (id1 < id2)
		{
			(id1 == 1) ? pushfront_path(start, tmp2)\
				: pushafter_path(start, (id1 - 1), tmp2);
			pushafter_path(start, (id2 - 1), tmp1);
		}
		else if (id1 > id2)
		{
			(id2 == 1) ? pushfront_path(start, tmp1)\
				: pushafter_path(start, (id2 - 1), tmp1);
			pushafter_path(start, (id1 - 1), tmp2);
		}
	}
}

/*
** Transfert un noeud d'une liste
** a une autre liste
*/
void					send_path_away(t_path **src, t_path **dst, uint32_t id)
{
	t_path			*tmp;

	if ((src != NULL && *src != NULL) && (dst != NULL))
	{
		tmp = remove_from_path(src, id, LM_TRUE);
		pushback_path(dst, tmp);
		update_id_path(dst);
	}
}
