/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_uint.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelemayi <kelemayi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 16:13:46 by kelemayi          #+#    #+#             */
/*   Updated: 2024/02/26 17:19:04 by kelemayi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_write_uint(unsigned int n)
{
	if (n > 9)
		ft_write_uint(n / 10);
	ft_putchar_fd(((n % 10) + 48), 1);
}

int	ft_print_uint(unsigned int n)
{
	unsigned int	i;

	i = 0;
	ft_write_uint(n);
	if (n == 0)
		return (1);
	while (n)
	{
		n = n / 10;
		i++;
	}
	return (i);
}
