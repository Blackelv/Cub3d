/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelemayi <kelemayi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 09:19:37 by kelemayi          #+#    #+#             */
/*   Updated: 2024/02/28 09:11:58 by kelemayi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_hex(unsigned long n, const char specifier)
{
	char	*case_b;
	int		len;

	if (specifier == 'x')
		case_b = "0123456789abcdef";
	else
		case_b = "0123456789ABCDEF";
	len = 0;
	if (n > 15)
		len += ft_print_hex(n / 16, specifier);
	ft_putchar_fd(*(case_b + (n % 16)), 1);
	len++;
	return (len);
}
