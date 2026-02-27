/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rev_rot_moves.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kel <kel@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 01:24:25 by kel               #+#    #+#             */
/*   Updated: 2025/02/20 00:26:44 by kel              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	rev_rotate(t_s_list **stack)
{
	t_s_list	*last_node;
	t_s_list	*sec_last_node;

	last_node = ft_lastnode(*stack);
	sec_last_node = *stack;
	while (sec_last_node->next->next)
		sec_last_node = sec_last_node->next;
	sec_last_node->next = NULL;
	last_node->next = *stack;
	*stack = last_node;
}

void	rra(t_s_list **a)
{
	rev_rotate(a);
	ft_putstr_fd("rra\n", 1);
}

void	rrb(t_s_list **b)
{
	rev_rotate(b);
	ft_putstr_fd("rrb\n", 1);
}

void	rrr(t_s_list **a, t_s_list **b)
{
	rev_rotate(a);
	rev_rotate(b);
	ft_putstr_fd("rrr\n", 1);
}
