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

t_node		**get_top_elem(t_list *lst)
{
	t_node	**ret;

	ret = NULL;
	if (lst != NULL)
		ret = (t_node**)(lst->content);
	return (ret);
}

void		del_address_lst(t_list **alst)
{
	t_list *keep;

	while (*alst)
	{
		keep = (*alst)->next;
		if ((*alst)->content)
		{
			free((*alst)->content);
			(*alst)->content = NULL;
		}
		free(*alst);
		*alst = keep;
	}
	*alst = NULL;
}
