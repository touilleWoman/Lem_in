/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_address.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleblond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 12:55:27 by jleblond          #+#    #+#             */
/*   Updated: 2019/11/30 12:55:30 by jleblond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solver.h"

void		debug_print_address_lst(t_list **alst)
{
	t_list *cp;
	t_node **node;

	cp = *alst;
	while (cp)
	{
		node = (t_node**)(cp->content);
		printf("[%s]", (*node)->name);
		cp = cp->next;
	}
	printf("\n");
}

t_list		*address_list_new(t_node ** const new)
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

// void		*address_list_add_bot(t_list **alist, t_node ** const new)
// {
// 	if (not_in_address_lst(*alst, *new))
// 		ft_lstadd_bot(&visited, address_list_new(current));
// }

void		del_first_elem(t_list **alst)
{
	t_list	*cp;

	if (*alst != NULL)
	{
		cp = *alst;
		*alst = (*alst)->next;
		free(cp->content);
		free(cp);
	}
}

