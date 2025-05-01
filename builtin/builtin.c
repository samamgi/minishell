/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aymen <aymen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 17:41:39 by aymen             #+#    #+#             */
/*   Updated: 2026/03/05 21:36:35 by aymen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_builtin(t_cmd *pipes)
{
	if (!pipes || !pipes->args || !pipes->args[0])
		return (0);
	if (ft_strncmp(pipes->args[0], "cd", 3) == 0 || ft_strncmp(pipes->args[0],
			"echo", 5) == 0 || ft_strncmp(pipes->args[0], "env", 4) == 0
		|| ft_strncmp(pipes->args[0], "exit", 5) == 0
		|| ft_strncmp(pipes->args[0], "export", 7) == 0
		|| ft_strncmp(pipes->args[0], "pwd", 4) == 0
		|| ft_strncmp(pipes->args[0], "unset", 6) == 0)
		return (1);
	return (0);
}

int	execute_builtin(t_cmd *pipes, t_env **env_list)
{
	if (ft_strncmp(pipes->args[0], "cd", 3) == 0)
		return (ft_cd(pipes, env_list));
	else if (ft_strncmp(pipes->args[0], "echo", 5) == 0)
		return (ft_echo(pipes));
	else if (ft_strncmp(pipes->args[0], "env", 4) == 0)
		return (ft_env(*env_list));
	else if (ft_strncmp(pipes->args[0], "exit", 5) == 0)
		return (ft_exit(pipes, env_list));
	else if (ft_strncmp(pipes->args[0], "export", 7) == 0)
		return (ft_export(pipes, env_list));
	else if (ft_strncmp(pipes->args[0], "pwd", 4) == 0)
		return (ft_pwd());
	else if (ft_strncmp(pipes->args[0], "unset", 6) == 0)
		return (ft_unset(pipes, env_list));
	return (-1);
}
