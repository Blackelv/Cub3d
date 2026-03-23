/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kel <kel@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 09:35:05 by kelemayi          #+#    #+#             */
/*   Updated: 2026/03/08 01:20:30 by kel              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*tstr;
	size_t	f;
	size_t	l;

	f = 0;
	if (!s1 || !set)
		return (NULL);
	l = ft_strlen(s1);
	while (s1[f] && ft_strchr(set, s1[f]))
		f++;
	while (s1[l - 1] && ft_strchr(set, s1[l - 1]) && l > f)
		l--;
	tstr = (char *)malloc(sizeof(char) * (l - f + 1));
	if (tstr == NULL)
		return (NULL);
	ft_strlcpy(tstr, &s1[f], l - f + 1);
	return (tstr);
}
/*
int	main(int ac, char *av[])
{
	char	*str;

	str = ft_strtrim(av[1], av[2]);
	if (ac == 3)
		printf ("%s\n", str);
	return (0);
}*/
