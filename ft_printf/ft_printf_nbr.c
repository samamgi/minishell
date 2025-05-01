/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_nbr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadi-ou <ssadi-ou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 10:36:24 by ssadi-ou          #+#    #+#             */
/*   Updated: 2024/12/05 09:57:41 by ssadi-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_nlen(int n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		n = -n;
		i++;
	}
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

int	ft_print_n(int n)
{
	long	nb;

	nb = n;
	if (nb < 0)
	{
		nb = -nb;
		write(1, "-", 1);
	}
	if (nb > 9)
	{
		ft_print_n(nb / 10);
		ft_print_n(nb % 10);
	}
	else
		ft_print_c(nb + 48);
	return (ft_nlen(n));
}

int	ft_ulen(unsigned int n)
{
	unsigned int	i;

	i = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

int	ft_print_u(unsigned int n)
{
	unsigned long	nb;

	nb = n;
	if (nb > 9)
	{
		ft_print_u(nb / 10);
		ft_print_u(nb % 10);
	}
	else
		ft_print_c(nb + 48);
	return (ft_ulen(n));
}
