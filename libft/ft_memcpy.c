/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelemayi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 16:40:41 by kelemayi          #+#    #+#             */
/*   Updated: 2024/01/22 16:40:45 by kelemayi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char		*d;
	const char	*s;
	int			i;

	i = 0;
	d = (char *)dest;
	s = (const char *)src;
	if (!dest && !src)
		return (0);
	while (n > 0)
	{
		d[i] = s[i];
		n--;
		i++;
	}
	return (d);
}
