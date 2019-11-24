/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_info.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabih <naali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 08:24:32 by nabih             #+#    #+#             */
/*   Updated: 2019/11/24 16:50:40 by nabih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef		GET_INFO_H
# define	GET_INFO_H

# include "lem_in.h"

/*
** Recuperation d'info
*/
int8_t					get_info(t_lemin *lem);
int8_t					get_nb_ants(t_lemin *lem);
int8_t					get_node(t_lemin *lem);
int8_t					get_path(t_lemin *lem);

#endif
