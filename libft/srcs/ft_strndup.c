/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabih <naali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 17:18:11 by nabih             #+#    #+#             */
/*   Updated: 2019/07/25 17:20:06 by nabih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char			*ft_strndup(const char *s1, size_t size)
{
	unsigned int	i;
	char			*s2;

	i = 0;
	if ((s2 = (char*)malloc(sizeof(char) * size)) == NULL)
		return (NULL);
	while (i < size && s1[i] != '\0')
	{
		s2[i] = s1[i];
		i = i + 1;
	}
	s2[i] = '\0';
	return (s2);
}
