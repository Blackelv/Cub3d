/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_target.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kel <kel@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 01:13:17 by kel               #+#    #+#             */
/*   Updated: 2025/02/20 00:26:05 by kel              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	positive_gap(int *gap, int *target, int *small_gap, int *tmp_pos)
{
	if (*gap > 0 && *gap < *small_gap)
	{
		*small_gap = *gap;
		*target = *tmp_pos;
	}
}

int	find_insert_pos(t_s_list **s_a, int indx_b, int gap, int target)
{
	t_s_list	*tmp;
	int			smallest_gap;
	int			smallest_index;

	tmp = *s_a;
	smallest_gap = INT_MAX;
	smallest_index = INT_MAX;
	while (tmp)
	{
		gap = tmp->index - indx_b;
		positive_gap(&gap, &target, &smallest_gap, &tmp->position);
		smallest_index = ft_smallest_index(tmp);
		tmp = tmp->next;
	}
	if (smallest_gap == INT_MAX)
	{
		tmp = *s_a;
		while (tmp->index == smallest_index)
			return (tmp->position);
		tmp = tmp->next;
	}
	return (target);
}

void	set_target_node(t_s_list **stack_a, t_s_list **stack_b)
{
	t_s_list	*tmp;
	int			pos;

	pos = 0;
	tmp = *stack_b;
	ft_stack_positioning(stack_a);
	ft_stack_positioning(stack_b);
	while (tmp)
	{
		pos = find_insert_pos(stack_a, tmp->index, 0, pos);
		tmp->target_node = pos;
		tmp = tmp->next;
	}
}
