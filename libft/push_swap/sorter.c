/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kel <kel@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 01:39:19 by kel               #+#    #+#             */
/*   Updated: 2025/02/20 00:27:02 by kel              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

int	ft_issorted(t_s_list *stack)
{
	while (stack->next)
	{
		if (stack->val > stack->next->val)
			return (0);
		stack = stack->next;
	}
	return (1);
}

void	ft_sort_three(t_s_list **stack)
{
	int	biggest;

	if (ft_issorted(*stack))
		return ;
	biggest = biggest_index(*stack);
	if ((*stack)->index == biggest)
		ra(stack);
	else if ((*stack)->next->index == biggest)
		rra(stack);
	if ((*stack)->index > (*stack)->next->index)
		sa(stack);
}

void	ft_sort_four(t_s_list **stack_a, t_s_list **stack_b)
{
	int	smallest;

	smallest = ft_smallest_index(*stack_a);
	if ((*stack_a)->index == smallest)
		pb(stack_a, stack_b);
	else if ((*stack_a)->next->index == smallest)
	{
		sa(stack_a);
		pb(stack_a, stack_b);
	}
	else if ((*stack_a)->next->next->index == smallest)
	{
		ra(stack_a);
		ra(stack_a);
		pb(stack_a, stack_b);
	}
	else
	{
		rra(stack_a);
		pb(stack_a, stack_b);
	}
	ft_sort_three(stack_a);
	pa(stack_a, stack_b);
}

void	ft_sort_five(t_s_list **stack_a, t_s_list **stack_b)
{
	t_variables	check;

	check.smallest = ft_smallest_index(*stack_a);
	check.pos = 0;
	check.current = *stack_a;
	while (check.current->index != check.smallest)
	{
		check.current = check.current->next;
		check.pos++;
	}
	if (check.pos <= 2)
		while (check.pos-- > 0)
			ra(stack_a);
	else
		while (check.pos++ < 5)
			rra(stack_a);
	pb(stack_a, stack_b);
	ft_sort_four(stack_a, stack_b);
	pa(stack_a, stack_b);
}

void	ft_start_sort(t_s_list **stack_a, t_s_list **stack_b, int size)
{
	int	size_of_b;
	int	*arr;

	if (!ft_issorted(*stack_a))
	{
		if (size == 2)
			sa(stack_a);
		else if (size == 3)
			ft_sort_three(stack_a);
		else if (size == 4)
			ft_sort_four(stack_a, stack_b);
		else if (size == 5)
			ft_sort_five(stack_a, stack_b);
		else
		{
			arr = list_to_array(*stack_a, size);
			ft_push_a_lis(stack_a, stack_b, arr, size);
			size_of_b = ft_listsize(*stack_b);
			size = ft_listsize(*stack_a);
			ft_sort_all(stack_a, stack_b, size, size_of_b);
		}
	}
}
