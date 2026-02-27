/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   full_sorter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kel <kel@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 01:34:33 by kel               #+#    #+#             */
/*   Updated: 2025/02/20 00:23:54 by kel              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	settle_stack(t_s_list **stack_a)
{
	int	smallest;
	int	size;

	size = ft_listsize(*stack_a);
	smallest = find_smallest_index_position(stack_a);
	if (smallest > size / 2)
	{
		while (smallest < size)
		{
			rra(stack_a);
			smallest++;
		}
	}
	else
	{
		while (smallest > 0)
		{
			ra(stack_a);
			smallest--;
		}
	}
}

int	fetch_moves(t_s_list **s_a, t_s_list **s_b, int size_a, int size_b)
{
	int			i;
	int			*move_a;
	int			*move_b;
	t_s_list	*tmp;

	i = 0;
	move_a = malloc(sizeof(move_a) * size_b);
	move_b = malloc(sizeof(move_b) * size_b);
	tmp = *s_b;
	while (i < size_b)
	{
		move_b[i] = calculate_mov_b(tmp->position, size_b);
		tmp = tmp->next;
		i++;
	}
	i = 0;
	tmp = *s_b;
	while (i < size_b && tmp)
	{
		move_a[i++] = calculate_mov_a(*s_a, tmp->val, size_a);
		tmp = tmp->next;
	}
	i = fall_moves(move_a, move_b, size_b);
	i = prepare_a(move_a[i], move_b[i], s_a, s_b);
	return (free (move_a), free (move_b), i);
}

void	ft_sort_all(t_s_list **s_a, t_s_list **s_b, int size_a, int size_b)
{
	int			move;

	while (*s_b)
	{
		size_a = ft_listsize(*s_a);
		size_b = ft_listsize(*s_b);
		set_target_node(s_a, s_b);
		move = fetch_moves(s_a, s_b, size_a, size_b);
		if (move < 0)
			while (move++ < 0)
				rrb(s_b);
		else if (move > 0)
			while (move-- > 0)
				rb(s_b);
		pa(s_a, s_b);
	}
	if (!ft_issorted(*s_a))
		settle_stack(s_a);
}
