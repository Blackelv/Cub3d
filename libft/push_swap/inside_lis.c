/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inside_lis.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kel <kel@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 01:25:08 by kel               #+#    #+#             */
/*   Updated: 2025/02/20 00:24:36 by kel              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

int	*end_index(int *lis_len, int size, int *end, int *max)
{
	int	i;
	int	*lis;

	i = 0;
	*max = 0;
	*end = 0;
	while (i < size)
	{
		if (lis_len[i] >= *max)
		{
			*max = lis_len[i];
			*end = i;
		}
		i++;
	}
	lis = malloc(sizeof(*lis) * (*max + 1));
	if (!lis)
		return (NULL);
	return (lis);
}
