/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelemayi <kelemayi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 17:14:02 by kelemayi          #+#    #+#             */
/*   Updated: 2024/05/03 10:57:51 by kelemayi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*newstr;
	size_t	i;
	size_t	ttsize;

	ttsize = ft_strlen(s1) + ft_strlen(s2);
	newstr = (char *)malloc(sizeof(char) * (ttsize + 1));
	if (newstr == 0)
		return (NULL);
	i = 0;
	while (*s1)
		newstr[i++] = *s1++;
	while (*s2)
	{
		newstr[i++] = *s2++;
	}
	newstr[i] = '\0';
	return (newstr);
}
/*
int	main(int ac, char **av)
{
	char	*newstr;
	
	newstr = ft_strjoin(av[1], av[2]);
	if (ac == 3)
	{
		printf ("%s\n", newstr);
		return (0);
	}
}*/
