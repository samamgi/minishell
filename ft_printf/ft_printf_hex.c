/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_hex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadi-ou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 10:29:14 by ssadi-ou          #+#    #+#             */
/*   Updated: 2024/12/05 09:43:34 by ssadi-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_hexlen(unsigned long long n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n /= 16;
		i++;
	}
	return (i);
}

void	ft_put_h(unsigned long long n, const char format)
{
	if (n >= 16)
	{
		ft_put_h((n / 16), format);
		ft_put_h((n % 16), format);
	}
	else
	{
		if (n <= 9)
			ft_print_c(n + 48);
		else
		{
			if (format == 'X')
				ft_print_c(n + 55);
			else
				ft_print_c(n + 87);
		}
	}
}

int	ft_print_h(unsigned long long n, const char format)
{
	if (n == 0)
		return (write(1, "0", 1));
	else
		ft_put_h(n, format);
	return (ft_hexlen(n));
}
