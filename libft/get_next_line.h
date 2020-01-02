/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleblond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/01 17:30:19 by jleblond          #+#    #+#             */
/*   Updated: 2020/01/02 20:48:23 by jleblond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include "libft.h"
# include <unistd.h>
# include <stdlib.h>

# define BUFF_SIZE 40
# define ERROR -1
# define SUCCESS 1
# define FINISHED 0

typedef enum	e_bool
{
	TRUE = 1,
	FALSE = 0,
}				t_bool;

int				get_next_line(int const fd, char **line);

#endif
