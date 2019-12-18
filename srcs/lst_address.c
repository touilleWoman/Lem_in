/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_address.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleblond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 12:55:27 by jleblond          #+#    #+#             */
/*   Updated: 2019/12/18 14:19:59 by naali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solver.h"

t_list		*address_list_new(t_node **const new)
{
	t_list *lst;

	lst = ft_lstnew((void const *)new, sizeof(t_node*));
	return (lst);
}

uint8_t		not_in_address_lst(t_list *lst, t_node const *address)
{
	while (lst != NULL)
	{
		if (address == *(t_node**)(lst->content))
			return (LM_FALSE);
		lst = lst->next;
	}
	return (LM_TRUE);
}

void		del_top_elem(t_list **alst)
{
	t_list	*cp;

	if (*alst)
	{
		cp = *alst;
		*alst = (*alst)->next;
		free(cp->content);
		cp->content = NULL;
		free(cp);
		cp = NULL;
	}
}

void		del_address_lst(t_list *lst)
{
	t_list *keep;

	while (lst)
	{
		keep = lst->next;
		free(lst->content);
		lst->content = NULL;
		free(lst);
		lst = keep;
	}
}

void		free_cir_tab(t_circuits **cir_tab, uint32_t tab_len)
{
	uint32_t	i;

	i = 0;
	if (cir_tab)
	{
		while (i < tab_len)
		{
			if (cir_tab[i])
			{
				del_address_lst(cir_tab[i]->addr);
				free(cir_tab[i]);
				cir_tab[i] = NULL;
			}
			i++;
		}
		free(cir_tab);
		cir_tab = NULL;
	}
}
