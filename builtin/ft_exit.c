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

static void	exit_cleanup(int code, t_cmd *pipes, t_env **env_list)
{
	clear_history();
	rl_clear_history();
	free_env(*env_list);
	free_cmd(pipes);
	exit(code);
}

static void	exit_numeric_error(t_cmd *pipes, t_env **env_list)
{
	ft_putendl_fd("exit", 2);
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(pipes->args[1], 2);
	ft_putendl_fd(": numeric argument required", 2);
	exit_cleanup(2, pipes, env_list);
}

static int	accumulate_exit_value(char *str, int sign, long long *number)
{
	unsigned long long	value;
	unsigned long long	limit;

	value = 0;
	limit = 9223372036854775807ULL + (sign == -1);
	while (*str && ft_isdigit(*str))
	{
		if (value > (limit - (*str - '0')) / 10)
			return (0);
		value = (value * 10) + (*str++ - '0');
	}
	if (*str)
		return (0);
	if (sign == -1 && value == 9223372036854775808ULL)
		*number = (-9223372036854775807LL - 1);
	else
		*number = (long long)(value * sign);
	return (1);
}

static int	is_numeric_exit_arg(char *str, long long *number)
{
	int	sign;

	if (!str || !*str)
		return (0);
	sign = 1;
	if (*str == '+' || *str == '-')
	{
		sign = 1 - (*str == '-') * 2;
		str++;
	}
	if (!*str)
		return (0);
	return (accumulate_exit_value(str, sign, number));
}

int	ft_exit(t_cmd *pipes, t_env **env_list)
{
	long long	exit_number;

	if (!pipes->args[1])
		return (ft_putendl_fd("exit", 2), exit_cleanup(0, pipes, env_list), 0);
	if (!is_numeric_exit_arg(pipes->args[1], &exit_number))
		exit_numeric_error(pipes, env_list);
	if (pipes->args[2])
	{
		ft_putendl_fd("minishell: exit: too many arguments", 2);
		g_shell.signumber = 1;
		return (1);
	}
	ft_putendl_fd("exit", 2);
	exit_cleanup((unsigned char)exit_number, pipes, env_list);
	return (0);
}
