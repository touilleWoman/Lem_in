/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naali <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 09:24:18 by naali             #+#    #+#             */
/*   Updated: 2019/11/20 12:00:11 by naali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

t_path					*new_path()
{
	t_path			*path;
	static uint32_t	id = 0;

	if ((path = malloc(sizeof(t_path))) == NULL)
		return (NULL);
	id++;
	path->id = id;
	path->taken = LM_FALSE;
	path->weight = 0;
	path->next = NULL;
	return (path);
}

void					pushback_path(t_path **start, t_path *node)
{
	t_path			*tmp;

	if (start == NULL)
		return ;
	if (start != NULL && *start != NULL && node != NULL)
	{
		tmp = get_last_path(start);
		tmp->next = node;
	}
	else if (start != NULL && *start == NULL)
		*start = node;
}

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
			ft_memdel((void**)&tmp1);
		}
		else
		{
			while (tmp1->next != NULL && tmp1->next->id != id)
				tmp1 = tmp1->next;
			if (tmp1->next != NULL && tmp1->next->id == id)
			{
				tmp2 = tmp1->next;
				tmp1->next = tmp1->next->next;
				ft_memdel((void**)&tmp2);
			}
		}
	}
}

void					clear_path(t_path **start)
{
	t_path			*tmp;

	if (start != NULL && *start != NULL)
	{
		tmp = *start;
		while (tmp != NULL)
		{
			*start = tmp->next;
			ft_memdel((void**)&tmp);
			tmp = *start;
		}
	}
}

static void				ft_swap(int *val1, int *val2)
{
	int				tmp;

	tmp = *val1;
	*val1 = *val2;
	*val2 = tmp;
}

void					swap_id_path(t_path *p1, t_path *p2)
{
	if (p1 != NULL && p2 != NULL)
		ft_swap((int*)&(p1->id), (int*)&(p2->id));
}
