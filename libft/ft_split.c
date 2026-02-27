/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelemayi <kelemayi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 12:07:27 by kelemayi          #+#    #+#             */
/*   Updated: 2024/05/10 11:25:57 by kelemayi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	good_alloc(char **wrd_arr, int loc, size_t buffer)
{
	int	i;

	i = 0;
	wrd_arr[loc] = malloc(buffer);
	if (wrd_arr[loc] == NULL)
	{
		while (i < loc)
			free(wrd_arr[i++]);
		free(wrd_arr);
		return (1);
	}
	return (0);
}

static int	pop_arr(char **wrd_arr, const char *s, char sep)
{
	size_t	len;
	int		i;

	i = 0;
	while (*s)
	{
		len = 0;
		while (*s == sep && *s)
			s++;
		while (*s != sep && *s)
		{
			len++;
			s++;
		}
		if (len)
		{
			if (good_alloc(wrd_arr, i, len + 1))
				return (1);
			ft_strlcpy(wrd_arr[i], s - len, len + 1);
			i++;
		}
	}
	return (0);
}

static size_t	count_words(const char *s, char sep)
{
	size_t	words;
	int		valid;

	words = 0;
	while (*s)
	{
		valid = 0;
		while (*s == sep && *s)
			s++;
		while (*s != sep && *s)
		{
			if (!valid)
			{
				words++;
				valid = 1;
			}
			s++;
		}
	}
	return (words);
}

char	**ft_split(char const *s, char c)
{
	size_t	words;
	char	**wrd_arr;

	words = count_words(s, c);
	wrd_arr = malloc(sizeof(char *) * (words + 1));
	if (wrd_arr == NULL)
		return (NULL);
	wrd_arr[words] = NULL;
	if (pop_arr(wrd_arr, s, c))
		return (NULL);
	return (wrd_arr);
}

/*int	main(int ac, char *av[])
{
	char	**s;

	s = ft_split(av[1], av[2][0]);
	if (ac == 3)
	{
		while (*s)
			printf("%s\n", *s++);
	}
	return (0);
}*/
