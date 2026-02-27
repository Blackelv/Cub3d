/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kel <kel@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 01:20:31 by kel               #+#    #+#             */
/*   Updated: 2025/02/20 00:26:15 by kel              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

int	ft_is_all_space(const char *str)
{
	while (*str)
	{
		if (!ft_isspace(*str))
			return (0);
		str++;
	}
	return (1);
}

void	ft_check_args(char **av, t_s_list **stack_a, t_flags mode)
{
	t_variables	check;

	check.i = 0;
	while (av[check.i])
	{
		if (ft_digit_args(av[check.i]) == 1)
			ft_error_exit(av, stack_a, mode);
		check.n = ft_atol(av[check.i]);
		if (check.n > INT_MAX || check.n < INT_MIN)
			ft_error_exit(av, stack_a, mode);
		if (ft_are_duplicates(&av[check.i]) == 1)
			ft_error_exit(av, stack_a, mode);
		ft_lstcreat_append(stack_a, (int)check.n);
		check.i++;
	}
	if (mode == ONE_ARGC)
		ft_free_st(av);
}
