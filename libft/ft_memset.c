/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelemayi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 15:30:01 by kelemayi          #+#    #+#             */
/*   Updated: 2024/01/22 15:30:05 by kelemayi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <stdio.h>
#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	char	*ptr;

	ptr = (char *)s;
	while (n > 0)
	{
		ptr[n - 1] = c;
		n--;
	}
	return (ptr);
}

/*int main()
{
	char	s[] = "Hello";
	size_t	n = 1;
	int	c = 'd';

	printf ("%p\n", ft_memset(s, c, n));
	printf ("%p\n", memset(s, c, n));
	return (0);
}*/
