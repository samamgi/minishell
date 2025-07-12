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

int	execslash(char *cmd, char **av, char *path, char **env)
{
	if ((ft_strnstr(cmd, "./", 2)) || !path || !env || (cmd[0] == '/') || (!cmd
			|| (cmd && ft_strlen(cmd) <= 0)))
	{
		if (check_exist(cmd) == 1)
		{
			if (!env)
				execve(cmd, av, NULL);
			else
				execve(cmd, av, env);
			free(path);
			return (1);
		}
		free(path);
		return (-1);
	}
	return (0);
}

void	execlast(char *slash, char **split_path, char **argv, char **env)
{
	char	*path;

	path = pathfinder(slash, split_path);
	if (path)
	{
		if (check_exist(path) == -1)
		{
			put_error(NULL, 2, argv);
			freeall(slash, path, split_path, NULL);
			exit(126);
			return ;
		}
		execve(path, argv, env);
		freeall(slash, path, split_path, argv);
		exit(1);
		return ;
	}
	freeall(slash, path, split_path, NULL);
	put_error(NULL, 1, argv);
	exit(127);
}

void	commande(char **cmd, char **env)
{
	char	*path;
	char	*slash;
	char	**split_path;
	char	**argv;

	path = getpath(env);
	argv = cmd;
	if (execslash(cmd[0], argv, path, env) != 0)
		return ;
	slash = ft_strjoin("/", argv[0]);
	split_path = ft_split(path, ':');
	if (!split_path || !slash || !argv)
	{
		freeall(slash, path, split_path, NULL);
		exit(-1);
		return ;
	}
	execlast(slash, split_path, argv, env);
}
