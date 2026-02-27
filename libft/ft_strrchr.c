/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelemayi <kelemayi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 11:50:56 by kelemayi          #+#    #+#             */
/*   Updated: 2024/01/26 13:35:05 by kelemayi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*pos;

	pos = NULL;
	while (*s != '\0')
	{
		if (*s == (char)c)
		{
			pos = (char *)s;
		}
		s++;
	}
	if ((char) c == '\0')
		return ((char *)s);
	return (pos);
}
