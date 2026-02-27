/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelemayi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 13:03:41 by kelemayi          #+#    #+#             */
/*   Updated: 2024/01/23 13:03:45 by kelemayi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	while (*s != (char)c)
	{
		if (*s == '\0')
			return (NULL);
		s++;
	}
	return ((char *)s);
}
/*
int	main()
{
	const char	*str = "Hello world";
	char		c = 'l';
	char		*result = ft_strchr(str, c);
	
	printf("%c %ld\n", c, result - str);
	printf("%c %s\n", c, ft_strchr(str, c));
	printf("%c %s\n", c, strchr(str, c));
	printf("%c", c);
	return (0);
}*/
