/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelemayi <kelemayi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 13:58:09 by kelemayi          #+#    #+#             */
/*   Updated: 2024/05/10 11:29:30 by kelemayi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	if (little[0] == '\0')
		return ((char *)big);
	i = 0;
	j = 0;
	while (big[i] && i < len)
	{
		while (big [i + j] == little[j] && i + j < len && big[i + j])
			j++;
		if (little[j] == '\0')
			return ((char *)big + i);
		i++;
		j = 0;
	}
	return (0);
}
/*
int	main()
{
	const char big[] = "Why does my soul, feel so bad";
	const char lil[] = "does";
	char	*ptr1;

	ptr1 = ft_strnstr(big, lil, 15);
	printf("%s", ptr1);
	return (0);
}*/
