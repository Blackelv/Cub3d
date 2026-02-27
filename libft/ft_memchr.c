/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelemayi <kelemayi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 16:40:25 by kelemayi          #+#    #+#             */
/*   Updated: 2024/05/03 10:52:12 by kelemayi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;
	char	*str;

	i = 0;
	str = (char *)s;
	while (i < n)
	{
		if ((unsigned char)str[i] == (unsigned char)c)
			return ((char *)s + i);
		i++;
	}
	return (NULL);
}
/*
int	main()
{
	char	str[] = "Play with fire";
	char	c = 'w';
	size_t	n = ft_strlen(str);
	char	*pos = ft_memchr(str, c, n);
	char	*pos1 = memchr(str, c, n);
	printf("%c\n", pos[0]);
	printf("%c\n", pos1[0]);
	printf("%p\n", ft_memchr(str, c, n));
	printf("%p\n", memchr(str, c, n));
	return (0);
}*/
