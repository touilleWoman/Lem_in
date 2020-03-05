/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naali <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 14:24:20 by naali             #+#    #+#             */
/*   Updated: 2020/01/03 15:38:52 by naali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "./libft.h"

char			*ft_strdup(const char *s1)
{
	unsigned int	i;
	char			*s2;

	i = 0;
	if ((s2 = (char *)malloc(sizeof(char) * (ft_strlen(s1) + 1))) == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		s2[i] = s1[i];
		i = i + 1;
	}
	s2[i] = '\0';
	return (s2);
}
