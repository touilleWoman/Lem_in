/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabih <naali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 08:23:51 by nabih             #+#    #+#             */
/*   Updated: 2019/12/18 13:56:09 by naali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <get_info.h>

static int8_t			clear_info(t_lemin *lem, int8_t flg)
{
	ft_memdel((void**)&(lem->line));
	lem->start = NULL;
	lem->end = NULL;
	clear_hashtab(lem);
	return (flg);
}

/*
** Recuperation
**    D'INFO
*/

int8_t					get_info(t_lemin *lem)
{
	int8_t			ret;

	lem->nb_nodes = 0;
	if ((ret = get_nb_ants(lem)) > 0)
	{
		if ((ret = get_node(lem)) == LM_SUCCESS)
		{
			if ((ret = get_path(lem)) == LM_ERROR)
				return (clear_info(lem, LM_ERROR));
		}
		else
			return (clear_info(lem, LM_ERROR));
	}
	return ((ret > 0) ? LM_SUCCESS : LM_ERROR);
}
