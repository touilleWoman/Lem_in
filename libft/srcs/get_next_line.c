/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabih <naali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 18:53:57 by nabih             #+#    #+#             */
/*   Updated: 2019/07/26 04:41:06 by nabih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include "get_next_line.h"

static unsigned int		check_str(char *str)
{
	unsigned int	i;

	i = 0;
	if (str != NULL)
	{
		while (str[i] != '\n' && str[i] != '\0')
			i++;
	}
	return (i);
}

static char				*choose_copy(char *tmp)
{
	if (ft_strchr(tmp, '\n'))
	{
		ft_strcpy(tmp, ft_strchr(tmp, '\n') + 1);
		return (tmp);
	}
	if (check_str(tmp) > 0)
	{
		tmp = ft_strcpy(tmp, ft_strchr(tmp, '\0'));
		return (tmp);
	}
	return (NULL);
}

int						get_next_line(int const fd, char **line)
{
	int			rd;
	int			check;
	static char	*tmp1 = NULL;
	char		*tmp2;
	char		buf[BUFF_SIZE + 1];

	rd = 0;
	check = 0;
	tmp2 = NULL;
	if (fd >= 0 && line && BUFF_SIZE > 0 && read(fd, buf, 0) >= 0)
	{
		*line = NULL;
		while ((tmp1 == NULL || tmp1[(check = check_str(tmp1))] != '\n')
			   && (rd = read(fd, buf, BUFF_SIZE)) > 0)
		{
			buf[rd] = '\0';
			tmp2 = tmp1;
			tmp1 = ft_strjoin(tmp1, buf);
			ft_memdel((void**)(&tmp2));
		}
		*line = ft_strsub(tmp1, 0, check);
		return ((choose_copy(tmp1) == NULL) ? 0 : 1);
	}
	return (-1);
}
