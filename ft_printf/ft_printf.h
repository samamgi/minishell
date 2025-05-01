/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadi-ou <ssadi-ou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 10:55:08 by ssadi-ou          #+#    #+#             */
/*   Updated: 2024/12/05 10:35:59 by ssadi-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "ft_printf.h"
# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

int		ft_print_c(int c);

int		ft_print_s(char *str);

int		ft_print_p(unsigned long long n, const char format);

int		ft_hexlen(unsigned long long n);

void	ft_put_h(unsigned long long n, const char format);

int		ft_print_h(unsigned long long n, const char format);

int		ft_print_n(int n);

int		ft_print_u(unsigned int n);

int		ft_printf(const char *format, ...);

#endif
