/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelemayi <kelemayi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 12:33:02 by kelemayi          #+#    #+#             */
/*   Updated: 2024/05/03 10:57:25 by kelemayi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	j;
	char	*sbstr;

	if (ft_strlen(s) <= start)
		return (ft_strdup(""));
	j = ft_strlen(s) - start;
	if (j > len)
		j = len;
	sbstr = (char *)malloc(sizeof(*s) * (j + 1));
	if (sbstr == NULL || !s)
		return (NULL);
	i = 0;
	while (i < j)
		sbstr[i++] = s[start++];
	sbstr[i] = '\0';
	return (sbstr);
}
/*
int	main(int argc, char **argv)
{
	char	*sbstr;
	
	if (argc == 2)
	{
		sbstr = ft_substr(argv[1], 0, 18446744073709551615);
		printf ("%s\n", sbstr);
		return (0);
	}
}*/
