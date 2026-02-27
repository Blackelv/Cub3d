/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelemayi <kelemayi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 15:03:57 by kelemayi          #+#    #+#             */
/*   Updated: 2024/02/28 18:13:13 by kelemayi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_finder(const char specifier, va_list ap)
{
	int	len;

	len = 0;
	if (specifier == 'c')
		len += ft_print_char(va_arg(ap, int));
	else if (specifier == 's')
		len += ft_print_str(va_arg(ap, char *));
	else if (specifier == 'p')
		len += (long)ft_print_adress(va_arg(ap, unsigned long));
	else if (specifier == 'd' || specifier == 'i')
		len += ft_print_int(va_arg(ap, int));
	else if (specifier == 'u')
		len += ft_print_uint(va_arg(ap, unsigned int));
	else if (specifier == 'x' || specifier == 'X')
		len += ft_print_hex((long)va_arg(ap, unsigned int), specifier);
	else if (specifier == '%')
		len += write (1, "%", 1);
	return (len);
}

int	ft_printf(const char *specifier, ...)
{
	int		len;
	va_list	ap;
	int		i;

	len = 0;
	i = 0;
	va_start(ap, specifier);
	while (specifier[i])
	{
		if (specifier[i] == '%' && specifier[i + 1] != '\0')
		{
			if (ft_strchr("cspdiuxX%", specifier[i++]))
				len += ft_finder(specifier[i++], ap);
			else
				len += ft_print_char(specifier[i++]);
		}
		else if (specifier[i] == '%' && specifier[i + 1] == '\0')
			return (-1);
		else
			len += ft_print_char(specifier[i++]);
	}
	va_end(ap);
	return (len);
}
/*
int	main(void)
{
	char	c = 'a';
	char	*str = "why does my soul";
	int	n = 5;
	(int)double	dec = 3.14210;
	int	*b = &n;
	unsigned long	ind = 2147483647;
	int	orig_func;
	int	my_func;
	int f;
	//int d;

	orig_func = printf("%d\n", dec);
	my_func = ft_printf("%d\n", dec);
	f = ft_printf("%%");
	ft_printf("valore f %d\n", f);
	//d = printf("%");
	//printf("%d\n", d);
	orig_func = printf("%c\n", c);
	my_func = ft_printf("%c\n", c);
	printf("orig = %d\nmyft = %d\n", orig_func, my_func);
	orig_func = printf("%i\n", n);
	my_func = ft_printf("%i\n", n);
	printf("orig = %d\nmyft = %d\n", orig_func, my_func);
	orig_func = printf("%s\n", str);
	my_func = ft_printf("%s\n", str);
	printf("orig = %d\nmyft = %d\n", orig_func, my_func);
	orig_func = printf("%lx\n", ind);
	my_func = ft_printf("%x\n", ind);
	printf("orig = %d\nmyft = %d\n", orig_func, my_func);
	ft_printf("%%%%\n");
	printf("orig = %d\nmyft = %d\n", orig_func, my_func);
	orig_func = printf("%p\n", b);
	my_func = ft_printf("%p\n", b);
	printf("orig = %d\nmyft = %d\n", orig_func, my_func);
	orig_func = printf("%lX\n", ind);
	my_func = ft_printf("%X\n", ind);
	printf("orig = %d\nmyft = %d\n", orig_func, my_func);
	return (0);
}*/
