/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kel <kel@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 01:39:00 by kel               #+#    #+#             */
/*   Updated: 2025/02/20 00:25:06 by kel              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

int	main(int ac, char *av[])
{
	t_s_list	*stack_a;
	t_s_list	*stack_b;
	t_variables	main;

	stack_a = NULL;
	stack_b = NULL;
	if (ac < 2 || (ac == 2 && av[1][0] == '\0'))
		return (0);
	else if (ac == 2)
	{
		if (ft_is_all_space(av[1]))
			return (0);
		main.onearg = ft_split(av[1], ' ');
		ft_check_args(main.onearg, &stack_a, ONE_ARGC);
	}
	else
		ft_check_args(av + 1, &stack_a, MORE_ARGC);
	main.size = ft_listsize(stack_a);
	ft_indexing_stack(stack_a, main.size);
	ft_start_sort(&stack_a, &stack_b, main.size);
	ft_free_stack(stack_a);
	return (0);
}
