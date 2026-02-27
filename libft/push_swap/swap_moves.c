/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_moves.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kel <kel@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 01:27:22 by kel               #+#    #+#             */
/*   Updated: 2025/02/20 00:27:10 by kel              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	swap(t_s_list **stack)
{
	int	tmp;
	int	tmp2;

	if (!stack || !*stack || !(*stack)->next)
		return ;
	tmp = (*stack)->val;
	tmp2 = (*stack)->index;
	(*stack)->val = (*stack)->next->val;
	(*stack)->index = (*stack)->next->index;
	(*stack)->next->val = tmp;
	(*stack)->next->index = tmp2;
}

void	sa(t_s_list **stack_a)
{
	swap(stack_a);
	ft_putstr_fd("sa\n", 1);
}

void	sb(t_s_list **stack_b)
{
	swap(stack_b);
	ft_putstr_fd("sb\n", 1);
}

void	ss(t_s_list **a, t_s_list **b)
{
	swap(a);
	swap(b);
	ft_putstr_fd("ss\n", 1);
}
