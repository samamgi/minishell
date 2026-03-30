/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdexec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aymen <aymen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 05:21:04 by ssadi-ou          #+#    #+#             */
/*   Updated: 2026/03/05 21:33:19 by aymen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../inc/pipex.h"

static void	child_cleanup_and_exit(int status, t_cmd *pipes, char **env)
{
	if (env)
		free_split(env);
	if (pipes)
		free_cmd(pipes);
	if (g_shell.env_global)
		free_env((t_env *)g_shell.env_global);
	clear_history();
	rl_clear_history();
	exit(status);
}

int	execslash(char *cmd, t_cmd *current, char *path, char **env)
{
	if ((ft_strnstr(cmd, "./", 2)) || !path || !env || (cmd[0] == '/') || (!cmd
			|| (cmd && ft_strlen(cmd) <= 0)))
	{
		if (check_exist(cmd) == 1)
		{
			if (!env)
				execve(cmd, current->args, NULL);
			else
				execve(cmd, current->args, env);
			return (1);
		}
		return (-1);
	}
	return (0);
}

void	execlast(t_exec *exec)
{
	char	*path;

	path = pathfinder(exec->slash, exec->split_path);
	if (path)
	{
		if (check_exist(path) == -1)
		{
			freeall(exec->slash, path, exec->split_path);
			child_cleanup_and_exit(126, exec->pipes, exec->env);
		}
		execve(path, exec->current->args, exec->env);
		freeall(exec->slash, path, exec->split_path);
		child_cleanup_and_exit(126, exec->pipes, exec->env);
	}
	put_error(NULL, 1, exec->current->args);
	freeall(exec->slash, path, exec->split_path);
	child_cleanup_and_exit(127, exec->pipes, exec->env);
}

static int	setup_exec_data(t_exec *exec, t_cmd *current,
	t_cmd *pipes, char **env)
{
	char	*path;

	path = getpath(env);
	if (execslash(current->args[0], current, path, env) != 0)
		return (1);
	exec->slash = ft_strjoin("/", current->args[0]);
	exec->split_path = ft_split(path, ':');
	if (!exec->split_path || !exec->slash || !current->args)
	{
		freeall(exec->slash, path, exec->split_path);
		return (1);
	}
	exec->env = env;
	exec->pipes = pipes;
	exec->current = current;
	return (0);
}

void	commande(char **env, t_cmd *pipes, t_cmd *current)
{
	t_exec	exec;
	t_env	*env_list;
	int		status;

	if (check_builtin(current))
	{
		env_list = set_env_list(env);
		status = execute_builtin(current, &env_list);
		free_env(env_list);
		child_cleanup_and_exit(status, pipes, env);
	}
	if (setup_exec_data(&exec, current, pipes, env))
		child_cleanup_and_exit(127, pipes, env);
	execlast(&exec);
}
