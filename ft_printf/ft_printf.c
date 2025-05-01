/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadi-ou <ssadi-ou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 10:12:47 by ssadi-ou          #+#    #+#             */
/*   Updated: 2024/12/05 10:36:06 by ssadi-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	checker(va_list arg, const char format)
{
	int	value;

	value = 0;
	if (format == 'c')
		value += ft_print_c(va_arg(arg, int));
	if (format == 's')
		value += ft_print_s(va_arg(arg, char *));
	if (format == 'p')
		value += ft_print_p(va_arg(arg, unsigned long long), format);
	if (format == 'i' || format == 'd')
		value += ft_print_n(va_arg(arg, int));
	if (format == 'u')
		value += ft_print_u(va_arg(arg, unsigned int));
	if (format == 'x' || format == 'X')
		value += ft_print_h(va_arg(arg, unsigned int), format);
	if (format == '%')
		value += write(1, "%", 1);
	return (value);
}

int	ft_printf(const char *format, ...)
{
	va_list	arg;
	int		value;
	int		i;

	if (!format)
		return (-1);
	value = 0;
	i = 0;
	va_start(arg, format);
	while (format[i])
	{
		if (format[i] == '%')
		{
			value += checker(arg, format[i + 1]);
			i++;
		}
		else
			value += ft_print_c(format[i]);
		i++;
	}
	va_end(arg);
	return (value);
}
