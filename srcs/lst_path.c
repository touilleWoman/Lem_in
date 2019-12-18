/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naali <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 09:24:18 by naali             #+#    #+#             */
/*   Updated: 2019/12/18 14:37:56 by naali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

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

void					swap_path_by_id(t_path **start, uint32_t id1,
										uint32_t id2)
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
