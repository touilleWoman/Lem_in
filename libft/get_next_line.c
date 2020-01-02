/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleblond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 14:43:47 by jleblond          #+#    #+#             */
/*   Updated: 2020/01/02 20:44:50 by jleblond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int		buf_to_line(char **line, char const buf[BUFF_SIZE], size_t n)
{
	char			str[n + 1];
	char			*tmp;

	ft_strncpy(str, buf, n);
	str[n] = '\0';
	if (*line == NULL)
		*line = ft_strdup(str);
	else
	{
		tmp = ft_strjoin(*line, str);
		if (tmp == NULL)
			return (ERROR);
		free(*line);
		*line = tmp;
	}
	if (*line == NULL)
		return (ERROR);
	return (SUCCESS);
}

static int		renew_buf(char **line, char buf[BUFF_SIZE], int *n_not_found)
{
	size_t			n;

	n = 0;
	while ((buf[n] != 0) && (buf[n] != '\n'))
		n++;
	if (buf_to_line(line, buf, n) == ERROR)
		return (ERROR);
	if (buf[n] == '\n')
		*n_not_found = FALSE;
	ft_memmove(buf, buf + n + 1, BUFF_SIZE - n);
	ft_memset(buf + BUFF_SIZE - n, '\0', n);
	return (SUCCESS);
}

int				get_next_line(const int fd, char **line)
{
	int				readret;
	static char		buf[BUFF_SIZE] = "\0";
	int				n_not_found;

	if (BUFF_SIZE < 1 || line == NULL || fd < 0)
		return (ERROR);
	*line = NULL;
	n_not_found = TRUE;
	while (n_not_found)
	{
		if (buf[0] == '\0')
		{
			readret = read(fd, buf, BUFF_SIZE);
			if (readret == ERROR)
				return (ERROR);
			else if (readret == 0 && *line == NULL)
				return (FINISHED);
			else if (readret == 0)
				return (SUCCESS);
		}
		if (renew_buf(line, buf, &n_not_found) == ERROR)
			return (ERROR);
	}
	return (SUCCESS);
}
