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

#include "../inc/pipex.h"
#include "../../minishell.h"

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

void	execlast(char *slash, char **split_path, char **env, t_cmd *pipes, t_cmd *current)
{
	char	*path;

	path = pathfinder(slash, split_path);
	if (path)
	{
		if (check_exist(path) == -1)
		{
			freeall(slash, path, split_path);
			free_cmd(pipes);
			exit(126);
		}
		execve(path, current->args, env);
		freeall(slash, path, split_path);
		free_cmd(pipes);
		exit(126);
	}
	put_error(NULL, 1, current->args);
	freeall(slash, path, split_path);
	free_cmd(pipes);
	exit(127);
}

void	commande(char **env, t_cmd *pipes, t_cmd *current)
{
	char	*path;
	char	*slash;
	char	**split_path;

	path = getpath(env);
	if (execslash(current->args[0], current, path, env) != 0)
	{
		free_cmd(pipes);
		exit(127);
	}
	slash = ft_strjoin("/", current->args[0]);
	split_path = ft_split(path, ':');
	if (!split_path || !slash || !current->args)
	{
		freeall(slash, path, split_path);
		free_cmd(pipes);
		exit(-1);
	}
	execlast(slash, split_path, env, pipes, current);
}
