/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabih <naali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/26 16:48:42 by nabih             #+#    #+#             */
/*   Updated: 2020/01/02 11:49:10 by jleblond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>
#include <get_info.h>

int				main(void)
{
	t_lemin		lem;

	lem.line = NULL;
	ft_bzero(lem.tab, sizeof(t_node*) * HASHCODE);
	if (HASHCODE > 100 && HASHCODE < 50000)
	{
		if (get_info(&lem) == LM_SUCCESS)
		{
			solver(&lem);
		}
		clear_hashtab(&lem);
	}
	return (0);
}
