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

int	execslash(char *cmd, t_cmd *pipes, char *path, char **env)
{
	if ((ft_strnstr(cmd, "./", 2)) || !path || !env || (cmd[0] == '/') || (!cmd
			|| (cmd && ft_strlen(cmd) <= 0)))
	{
		if (check_exist(cmd) == 1)
		{
			if (!env)
				execve(cmd, pipes->args, NULL);
			else
				execve(cmd, pipes->args, env);
			free(path);
			return (1);
		}
		free(path);
		return (-1);
	}
	return (0);
}

void	execlast(char *slash, char **split_path, char **env, t_cmd *pipes)
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
		execve(path, pipes->args, env);
		freeall(slash, path, split_path);
		free_cmd(pipes);
		exit(126);
	}
	put_error(NULL, 1, pipes->args);
	freeall(slash, path, split_path);
	free_cmd(pipes); // ici il faut pas free toute la structure mais ce qui est dans la structure est deja free, ou ? jsp
	exit(127);
}

void	commande(char **env, t_cmd *pipes)
{
	char	*path;
	char	*slash;
	char	**split_path;

	path = getpath(env);
	if (execslash(pipes->args[0], pipes, path, env) != 0)
		return ;
	slash = ft_strjoin("/", pipes->args[0]);
	split_path = ft_split(path, ':');
	if (!split_path || !slash || !pipes->args)
	{
		freeall(slash, path, split_path);
		free_cmd(pipes);
		exit(-1);
	}
	execlast(slash, split_path, env, pipes);
}
