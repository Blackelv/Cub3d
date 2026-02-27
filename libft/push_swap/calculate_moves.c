/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_moves.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kel <kel@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 01:18:26 by kel               #+#    #+#             */
/*   Updated: 2025/02/20 00:23:33 by kel              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

int	max_element(t_s_list *stack, int *index)
{
	int	max;

	max = stack->val;
	*index = 1;
	ft_positioning(&stack);
	while (stack)
	{
		if (stack->val > max)
		{
			max = stack->val;
			*index = stack->position;
		}
		stack = stack->next;
	}
	return (max);
}

int	min_element(t_s_list *stack, int *index)
{
	int	min;

	min = INT_MAX;
	*index = 0;
	ft_stack_positioning(&stack);
	while (stack)
	{
		if (stack->val < min)
		{
			min = stack->val;
			*index = stack->position;
		}
		stack = stack->next;
	}
	return (min);
}

int	find_next_larger(t_s_list *stack_a, int b)
{
	t_s_list	*tmp;
	int			index;

	tmp = stack_a;
	index = 1;
	if (stack_a->val > b && b > (lastnode_val(stack_a)))
		return (0);
	while (!(tmp->val < b && tmp->next->val > b))
	{
		tmp = tmp->next;
		index++;
	}
	return (index);
}

int	calculate_mov_b(int index, int size)
{
	if (index <= size / 2)
		return (index);
	else
		return (index - size);
}

int	calculate_mov_a(t_s_list *stack_a, int b, int size_a)
{
	int	index;

	if (max_element(stack_a, &index) < b)
	{
		if (index <= size_a / 2)
			return (index);
		else
			return (index - (size_a));
	}
	if (min_element(stack_a, &index) > b)
	{
		if (index <= size_a / 2)
			return (index);
		else
			return (index - size_a);
	}
	index = find_next_larger(stack_a, b);
	if (index <= size_a / 2)
		return (index);
	else
		return (index - size_a);
}
