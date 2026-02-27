/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelemayi <kelemayi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 13:01:15 by kelemayi          #+#    #+#             */
/*   Updated: 2024/05/03 10:52:38 by kelemayi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;
	char	*str1;
	char	*str2;

	i = 0;
	str1 = (char *)s1;
	str2 = (char *)s2;
	if (n == 0)
		return (0);
	while (str1[i] == str2[i] && i < n -1)
		i++;
	return ((unsigned char)str1[i] - (unsigned char)str2[i]);
}

/*
int	main()
{
	char	s1[] = "Why should I stay";
	char	s2[] = "In the deepest Ocean";
	
	printf(":%d:\n", ft_memcmp(s1, s2, 3));
	printf(":%d:\n", memcmp(s1, s2, 3));
	return (0);
}*/
