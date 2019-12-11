/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ants.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleblond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 12:45:26 by jleblond          #+#    #+#             */
/*   Updated: 2019/12/11 06:47:24 by nabih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solver.h"

static uint32_t			how_many_path(t_circuits **c, uint32_t len,
										uint32_t ants)
{
	uint32_t		len_tmp;
	t_manypth		mp;

	mp.old = 0;
	mp.not_use = 0;
	len_tmp = len;
	while (--len + 1 > 0)
	{
		mp.ratio = ants / (len + 1);
		if (mp.ratio > 0)
		{
			mp.new = c[len]->nb_floor + (mp.ratio - 1);
			if ((mp.new <= mp.old || mp.old == 0))
			{
				if (mp.old != 0)
					mp.not_use++;
				mp.old = mp.new;
			}
		}
		else
			mp.not_use++;
	}
	return (mp.not_use);
}

static void				init_ant_cir(t_circuits **c, t_list **ants, int32_t nb)
{
	int32_t			i;
	t_list			*tmp;

	i = 0;
	if (c && *c && ants && *ants && nb > 0)
	{
		tmp = *ants;
		while (tmp->content)
			tmp = tmp->next;
		while (i < nb)
		{
			tmp->content = (void*)(c[i]->addr)->next;
			tmp = tmp->next;
			i++;
		}
	}
}

static void				print_one_ant(uint32_t ant_index, char *node_name)
{
	ft_putchar('L');
	ft_putnbr(ant_index);
	ft_putchar('-');
	ft_putstr(node_name);
}

static int32_t			print_line(t_list **ants, int32_t nb)
{
	int32_t			end;
	size_t			cs;
	t_list			*tmp;
	t_list			*cp;
	t_node			*node;

	end = 0;
	tmp = *ants;
	while (nb > 0)
	{
		cp = (t_list*)(tmp->content);
		node = *(t_node**)(cp->content);
		print_one_ant(tmp->content_size, node->name);
		cs = tmp->content_size;
		cp = cp->next;
		tmp->content = (void*)cp;
		tmp = tmp->next;
		if (cp == NULL)
		{
			ft_lstdel_contentsize(ants, cs);
			++end;
		}
		(--nb > 0) ? ft_putchar(' ') : 0;
	}
	return (end);
}

void					print_ants(t_lemin *lem, t_list **ants, t_circuits **cir_tab, int32_t tab_len)
{
	int32_t			total_enter;
	int32_t			send;
	int32_t			total_exit;
	int32_t			n_use;
	int				line;// a delete

	line = 0;// a delete
	total_enter = 0;
	total_exit = 0;
	while (ants && *ants)
	{
		send = 0;
		if (lem->nb_ants - total_enter > 0)
		{
			n_use = how_many_path(cir_tab, tab_len, lem->nb_ants - total_enter);
			send = tab_len - n_use;
			init_ant_cir(cir_tab, ants, send);
			total_enter += send;
		}
		total_exit += print_line(ants, total_enter - total_exit);
		ft_putchar('\n');
		line++;// a delete
	}
	printf("Reste == %d\n", lem->nb_ants - total_enter);// a delete
	printf("Enter == %d, Exit == %d\n", total_enter, total_exit);// a delete
	printf("nb line == %d\n", line);// a delete
}
