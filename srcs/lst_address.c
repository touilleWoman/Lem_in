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


void		del_top_elem(t_list **alst)
{
	t_list	*cp;

	if (*alst != NULL)
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

void		free_circuits(t_list **circuits, uint32_t cir_nb)
{
	if (circuits)
	{
		while(cir_nb)
		{
			del_address_lst(circuits[cir_nb - 1]);
			cir_nb--;
		}
		free(circuits);
		circuits = NULL;
	}
}
