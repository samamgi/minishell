/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aymen <aymen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 17:41:53 by aymen             #+#    #+#             */
/*   Updated: 2026/03/05 21:02:36 by aymen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_numeric_exit_arg(char *str, long long *number)
{
	int					sign;
	unsigned long long	value;
	unsigned long long	limit;

	if (!str || !*str)
		return (0);
	sign = 1;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	if (!*str)
		return (0);
	value = 0;
	limit = 9223372036854775807ULL;
	if (sign == -1)
		limit = 9223372036854775808ULL;
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		if (value > (limit - (*str - '0')) / 10)
			return (0);
		value = (value * 10) + (*str - '0');
		str++;
	}
	if (sign == -1 && value == 9223372036854775808ULL)
		*number = (-9223372036854775807LL - 1);
	else
		*number = (long long)(value * sign);
	return (1);
}

int ft_exit(t_cmd *pipes, t_env **env_list)
{
    long long	exit_number;

    if (!pipes->args[1])
    {
        ft_putendl_fd("exit", 2);
        free_env(*env_list);
        free_cmd(pipes);
        exit(0);
    }
    if (!is_numeric_exit_arg(pipes->args[1], &exit_number))
    {
        ft_putendl_fd("exit", 2);
        ft_putstr_fd("minishell: exit: ", 2);
        ft_putstr_fd(pipes->args[1], 2);
        ft_putendl_fd(": numeric argument required", 2);
        free_env(*env_list);
        free_cmd(pipes);
        exit(2);
    }
    if (pipes->args[2])
    {
        ft_putendl_fd("minishell: exit: too many arguments", 2);
        g_signumber = 1;
        return (1);
    }
    ft_putendl_fd("exit", 2);
    free_env(*env_list);
    free_cmd(pipes);
    exit((unsigned char)exit_number);
}