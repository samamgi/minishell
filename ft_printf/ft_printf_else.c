/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_else.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadi-ou <ssadi-ou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 10:22:34 by ssadi-ou          #+#    #+#             */
/*   Updated: 2024/12/05 09:45:32 by ssadi-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_c(int c)
{
	return (write(1, &c, 1));
}

int	ft_print_s(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (write(1, "(null)", 6));
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
	return (i);
}

int	ft_print_p(unsigned long long n, const char format)
{
	int	value;

	value = 0;
	if (n == 0)
		return (write(1, "(nil)", 5));
	else
	{
		value += write(1, "0x", 2);
		ft_put_h(n, format);
		value += ft_hexlen(n);
	}
	return (value);
}
