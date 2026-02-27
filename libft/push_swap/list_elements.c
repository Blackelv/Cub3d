/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_elements.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kel <kel@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 01:23:17 by kel               #+#    #+#             */
/*   Updated: 2025/02/20 00:24:51 by kel              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	ft_positioning(t_s_list **stack)
{
	t_s_list	*tmp;
	int			pos;

	pos = 1;
	tmp = *stack;
	while (tmp)
	{
		tmp->position = pos;
		tmp = tmp->next;
		pos++;
	}
}

void	ft_stack_positioning(t_s_list **stack)
{
	t_s_list	*tmp;
	int			pos;

	pos = 0;
	tmp = *stack;
	while (tmp)
	{
		tmp->position = pos;
		tmp = tmp->next;
		pos++;
	}
}

int	find_smallest_index_position(t_s_list **stack)
{
	t_s_list	*tmp;
	int			lowest_index;
	int			lowest_pos;

	tmp = *stack;
	lowest_index = INT_MAX;
	ft_stack_positioning(stack);
	lowest_pos = tmp->position;
	while (tmp)
	{
		if (tmp->index < lowest_index)
		{
			lowest_index = tmp->index;
			lowest_pos = tmp->position;
		}
		tmp = tmp->next;
	}
	return (lowest_pos);
}

int	biggest_index(t_s_list *stack)
{
	int	highest;

	highest = stack->index;
	while (stack)
	{
		if (stack->index > highest)
			highest = stack->index;
		stack = stack->next;
	}
	return (highest);
}

int	ft_smallest_index(t_s_list *stack)
{
	int	lowest;

	lowest = stack->index;
	while (stack)
	{
		if (stack->index < lowest)
			lowest = stack->index;
		stack = stack->next;
	}
	return (lowest);
}
