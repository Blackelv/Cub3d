/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelemayi <kelemayi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 18:21:12 by kelemayi          #+#    #+#             */
/*   Updated: 2024/05/08 11:45:25 by kelemayi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stddef.h>
# include <string.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <fcntl.h>
# include "../includes/libft.h"
//# include "../includes/push_swap.h"

/*******************************************************************************
*				Main_function:				       *
*******************************************************************************/
int	ft_printf(const char *specifier, ...);

/*******************************************************************************
*				Printf_utils_function:			       *
*******************************************************************************/
int	ft_print_char(int c);
int	ft_print_str(char *str);
int	ft_print_int(long n);
int	ft_print_uint(unsigned int n);
int	ft_print_hex(unsigned long n, const char specifier);
int	ft_print_adress(unsigned long adress);

#endif
