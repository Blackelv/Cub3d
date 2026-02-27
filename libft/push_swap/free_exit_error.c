/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exit_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kel <kel@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 01:16:34 by kel               #+#    #+#             */
/*   Updated: 2025/02/20 00:23:46 by kel              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	ft_free_st(char **mtx)
{
	int	i;

	i = 0;
	while (mtx[i])
	{
		free(mtx[i]);
		i++;
	}
	free(mtx);
}

void	ft_free_stack(t_s_list *stack)
{
	t_s_list	*tmp;

	while (stack)
	{
		tmp = stack;
		stack = stack->next;
		free(tmp);
	}
}

void	ft_error_exit(char **av, t_s_list **stack_a, t_flags mode)
{
	if (mode == ONE_ARGC)
		ft_free_st(av);
	ft_free_stack(*stack_a);
	write(2, "Error\n", 6);
	exit(1);
}
