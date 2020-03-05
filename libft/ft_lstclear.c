/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naali <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/03 15:45:28 by naali             #+#    #+#             */
/*   Updated: 2020/01/03 15:51:17 by naali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

void		ft_lstclear(t_list **alst)
{
	t_list	*tmp;

	tmp = NULL;
	if (alst != NULL)
		while (*alst != NULL)
		{
			tmp = (*alst)->next;
			ft_memdel((void**)alst);
			*alst = tmp;
		}
}
