/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelemayi <kelemayi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 18:53:52 by kelemayi          #+#    #+#             */
/*   Updated: 2024/05/03 10:56:21 by kelemayi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	int		i;
	char	*strd;

	i = 0;
	strd = (char *)malloc(sizeof(char) * ft_strlen(s) + 1);
	if (strd == NULL)
		return (NULL);
	while (s[i] != '\0')
	{
		strd[i] = s[i];
		i++;
	}
	strd[i] = '\0';
	return (strd);
}
/*
int	main(int argc, char **argv)
{
	char	*mine;
	char	*standard;
	
	if (argc == 2)
	{
		mine = ft_strdup(argv[1]);
		standard = strdup(argv[1]);
		printf ("%s:\n%s:\n", mine, standard);
	}
}*/
