/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdexec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadi-ou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 05:21:04 by ssadi-ou          #+#    #+#             */
/*   Updated: 2025/05/18 16:05:12 by ssadi-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../inc/pipex.h"

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
			free_cmd(exec->pipes);
			exit(126);
		}
		execve(path, exec->current->args, exec->env);
		freeall(exec->slash, path, exec->split_path);
		free_cmd(exec->pipes);
		exit(126);
	}
	put_error(NULL, 1, exec->current->args);
	freeall(exec->slash, path, exec->split_path);
	free_cmd(exec->pipes);
	exit(127);
}

void	commande(char **env, t_cmd *pipes, t_cmd *current)
{
    char	*path;
    t_exec	exec;
    t_env	*env_list;

    // Vérifier si c'est un builtin
    if (is_builtin(current))
    {
        env_list = set_env_list(env);
        execute_builtin(current, &env_list);
        free_env(env_list);
        free_cmd(pipes);
        exit(0);
    }
    path = getpath(env);
    if (execslash(current->args[0], current, path, env) != 0)
    {
        free_cmd(pipes);
        exit(127);
    }
    exec.slash = ft_strjoin("/", current->args[0]);
    exec.split_path = ft_split(path, ':');
    if (!exec.split_path || !exec.slash || !current->args)
    {
        freeall(exec.slash, path, exec.split_path);
        free_cmd(pipes);
        exit(-1);
    }
    exec.env = env;
    exec.pipes = pipes;
    exec.current = current;
    execlast(&exec);
}
