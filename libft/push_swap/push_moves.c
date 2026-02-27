/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_moves.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kel <kel@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 01:19:59 by kel               #+#    #+#             */
/*   Updated: 2025/02/20 00:26:27 by kel              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	push(t_s_list **from, t_s_list **to)
{
	t_s_list	*pop;

	if (!from || !*from)
		return ;
	pop = *from;
	*from = (*from)->next;
	if (!*to)
	{
		*to = pop;
		pop->next = NULL;
	}
	else
	{
		pop->next = *to;
		*to = pop;
	}
}

void	pa(t_s_list **a, t_s_list **b)
{
	push(b, a);
	ft_putstr_fd("pa\n", 1);
}

void	pb(t_s_list **a, t_s_list **b)
{
	push(a, b);
	ft_putstr_fd("pb\n", 1);
}
