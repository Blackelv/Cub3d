/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_adress.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelemayi <kelemayi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 13:13:16 by kelemayi          #+#    #+#             */
/*   Updated: 2024/02/27 17:23:42 by kelemayi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_adress(unsigned long adress)
{
	int					len;
	unsigned long long	cast;

	len = 0;
	if (!adress)
	{
		ft_putstr_fd("(nil)", 1);
		return (5);
	}
	cast = (unsigned long long)adress;
	len += write (1, "0x", 2);
	len += ft_print_hex(cast, 'x');
	return (len);
}
