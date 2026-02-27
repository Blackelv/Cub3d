/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lis.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kel <kel@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 01:41:10 by kel               #+#    #+#             */
/*   Updated: 2025/02/20 00:24:44 by kel              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

int	*list_to_array(t_s_list *stack, int size)
{
	int	*arr;
	int	i;

	i = 0;
	arr = malloc(sizeof(*arr) * size + 1);
	if (!arr)
		return (NULL);
	while (stack)
	{
		arr[i] = stack->val;
		stack = stack->next;
		i++;
	}
	return (arr);
}

int	size_of_lis(int *lis)
{
	int	i;

	i = 0;
	while (lis[i] != 0)
		i++;
	return (i);
}

int	*get_lis(int *arr, int *lis_len, int *prev, int size)
{
	int	i;
	int	j;
	int	end;
	int	*lis;
	int	max;

	lis = end_index(lis_len, size, &end, &max);
	lis[max] = INT_MAX;
	if (!lis)
		return (NULL);
	j = max - 1;
	i = end;
	while (i >= 0)
	{
		lis[j--] = arr[i];
		if (prev[i] == -1)
			break ;
		i = prev[i];
	}
	free(prev);
	free(arr);
	free(lis_len);
	return (lis);
}

int	*search_lis(int *arr, int size)
{
	int		i;
	int		j;
	int		*lis_len;
	int		*prev;

	i = -1;
	lis_len = malloc(sizeof(*lis_len) * size);
	prev = malloc(sizeof((*prev)) * size);
	if (!lis_len || !prev)
		return (NULL);
	while (++i < size)
	{
		lis_len[i] = 1;
		prev[i] = -1;
		j = -1;
		while (++j < i)
		{
			if (arr[i] > arr[j] && lis_len[i] < lis_len[j] + 1)
			{
				lis_len[i] += 1;
				prev[i] = j;
			}
		}
	}
	return (get_lis(arr, lis_len, prev, size));
}

void	ft_push_a_lis(t_s_list **s_a, t_s_list **s_b, int *arr, int size)
{
	int	i;
	int	j;
	int	*pos_of_lis;

	i = 0;
	j = 0;
	pos_of_lis = search_lis(arr, size);
	while (i < size && j < size)
	{
		if ((*s_a)->val == pos_of_lis[j])
		{
			ra(s_a);
			j++;
		}
		else
			pb(s_a, s_b);
		i++;
	}
	free(pos_of_lis);
}
