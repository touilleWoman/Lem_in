/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_anthill.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleblond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 19:06:30 by jleblond          #+#    #+#             */
/*   Updated: 2019/12/04 19:06:32 by jleblond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solver.h"



void		print_line(uint32_t ant_index, char *node_name)
{
	ft_putchar('L');
	ft_putnbr(ant_index);
	ft_putchar('-');
	ft_putstr(node_name);
	ft_putchar(' ');
}

void		print_anthill(t_lemin *lem, t_circuits **cir_tab,
							int32_t tab_len, t_anthill *h)
{
	uint32_t 		ant_index;
	char			*node_name;
	int32_t			i;
	uint32_t		floor;
	uint32_t		print_nb;

	if (h->activated == LM_FALSE)
		return ;
	i = 0;
	print_nb = h->nb_inside;
	ant_index = h->max_ant_index;
	floor = h->start_floor;
	while (print_nb > 0)
	{
		while (i < tab_len && print_nb > 0)
		{
			node_name = get_node_in_circuit(cir_tab[i]->addr, floor);
			if (!node_name)
				printf("can't get node name\n");
			// else
			// 	printf("name:%s\n", node_name);
			print_line(ant_index, node_name);
			if (ft_strcmp(node_name, (lem->end)->name) == 0)
			{
				h->total_exit++;
				h->nb_inside--;
			}
			i++;
			ant_index--;
			print_nb--;
		}
		i = 0;
		floor++;
	}
}

