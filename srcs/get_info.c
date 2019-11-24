/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabih <naali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 08:23:51 by nabih             #+#    #+#             */
/*   Updated: 2019/11/24 17:57:19 by nabih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <get_info.h>

static int8_t			clear_info(t_lemin *lem, int8_t flg)
{
	ft_memdel((void**)&(lem->line));
	ft_memdel((void**)&(lem->start));
	ft_memdel((void**)&(lem->end));
	clear_hashtab(lem);
	clear_hashpth(lem);
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
			ret = get_path(lem);
			if (ret == LM_SUCCESS)// A DELETE
				print_tab(lem->tab, HASHCODE);// A DELETE
		}
		else
			return (clear_info(lem, LM_ERROR));
	}
	return ((ret > 0) ? LM_SUCCESS : LM_ERROR);
}
