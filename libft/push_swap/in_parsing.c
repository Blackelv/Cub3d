/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kel <kel@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 01:24:44 by kel               #+#    #+#             */
/*   Updated: 2025/02/20 00:24:00 by kel              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

int	ft_digit_args(char *av)
{
	t_variables	data;

	data.i = 0;
	if (ft_issign(av[data.i]) && !av[data.i + 1])
		return (1);
	if (ft_issign(av[data.i]) == 1)
		data.i++;
	if (av[data.i] == '0' && ft_isdigit(av[data.i + 1]) == 1)
		return (1);
	while (av[data.i])
	{
		if (ft_isdigit(av[data.i]) == 0)
			return (1);
		data.i++;
	}
	return (0);
}

long	ft_atol(const char *str)
{
	t_variables	check;

	check.n = 0;
	check.sign = 1;
	check.i = 0;
	while (str[check.i] && ft_isspace(str[check.i]) == 1)
		check.i++;
	if (ft_issign(str[check.i]) == 1)
	{
		if (str[check.i] == 45)
			check.sign *= -1;
		check.i++;
	}
	while (str[check.i] && ft_isdigit(str[check.i]) == 1)
	{
		check.n = check.n * 10 + (str[check.i] - '0');
		check.i++;
	}
	return (check.n * check.sign);
}

int	ft_are_duplicates(char **av)
{
	t_variables	check;

	check.i = 0;
	while (av[check.i])
	{
		check.j = check.i + 1;
		while (av[check.j])
		{
			if (check.i != check.j
				&& ft_atoi(av[check.i]) == ft_atoi(av[check.j]))
				return (1);
			check.j++;
		}
		check.i++;
	}
	return (0);
}
