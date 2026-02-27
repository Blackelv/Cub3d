/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelemayi <kelemayi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 15:32:37 by kelemayi          #+#    #+#             */
/*   Updated: 2024/05/02 10:29:32 by kelemayi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc_gnl(size_t nmemb, size_t size)
{
	void	*mem;
	size_t	n;

	mem = malloc(nmemb * size);
	if (mem == NULL)
		return (NULL);
	n = nmemb * size;
	while (n > 0)
	{
		((char *)mem)[n - 1] = '\0';
		n--;
	}
	return (mem);
}

size_t	ft_strlen_gnl(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strchr_gnl(const char *s, int c)
{
	while (*s != (char)c)
	{
		if (*s == '\0')
			return (NULL);
		s++;
	}
	return ((char *)s);
}

char	*ft_strjoin_gnl(char *container, char *store_line)
{
	char	*newstr;
	size_t	i;
	size_t	ttsize;

	ttsize = ft_strlen_gnl(container) + ft_strlen_gnl(store_line);
	newstr = (char *)ft_calloc_gnl(sizeof(char), (ttsize + 1));
	if (!newstr || !store_line)
		return (NULL);
	i = 0;
	if (container != NULL)
	{
		while (*container)
			newstr[i++] = *container++;
	}
	while (*store_line)
		newstr[i++] = *store_line++;
	newstr[i] = '\0';
	return (newstr);
}
