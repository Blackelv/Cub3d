/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelemayi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 08:53:03 by kelemayi          #+#    #+#             */
/*   Updated: 2023/11/27 11:16:56 by kelemayi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	dlen;
	size_t	slen;

	i = 0;
	dlen = ft_strlen(dst);
	slen = ft_strlen(src);
	if (size == 0 || size <= dlen)
		return (slen + size);
	while (src[i] != '\0' && i < size - dlen - 1)
	{
		dst[dlen + i] = src[i];
		i++;
	}
	dst[dlen + i] = '\0';
	return (dlen + slen);
}
/*
int	main(void)
{
	char	src[] = "fear those who wield it...";
	char	dest[] = "Do not fear power, ";
	size_t	m;
	size_t	n;
	size_t	s;

	m = ft_strlen(src);
	n = ft_strlen(dest);
	s = m + n + 1;
	printf("%ld \n%s \n",ft_strlcat(dest, src, s), dest);
	return (0);
}*/
