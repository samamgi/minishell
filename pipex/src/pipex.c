/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadi-ou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 23:54:49 by ssadi-ou          #+#    #+#             */
/*   Updated: 2025/05/18 20:39:49 by ssadi-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../inc/pipex.h"

static void	fork_and_exec(t_cmd *pipes, t_cmd *cur, char **env, int *fds)
{
	if (fork() == 0)
	{
		setup_child_fds(cur, fds[0], &fds[1]);
		close_pipes(fds[0], &fds[1], cur);
		commande(env, pipes, cur);
		exit(1);
	}
}

static void	execute_child(t_cmd *pipes, t_cmd *current, char **env)
{
	int	fds[3];

	fds[0] = -1;
	while (current)
	{
		if (current->next && pipe(&fds[1]) == -1)
		{
			perror("pipe");
			exit(1);
		}
		fork_and_exec(pipes, current, env, fds);
		if (fds[0] != -1)
			close(fds[0]);
		if (current->next)
		{
			close(fds[2]);
			fds[0] = fds[1];
		}
		current = current->next;
	}
	while (wait(NULL) != -1)
		;
}

static int	execute_single(t_cmd *pipes, char **env)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
		solochild(pipes, env);
	wait(NULL);
	return (0);
}

int	pipex(t_cmd *pipes, char **env)
{
	if (!pipes)
		return (1);
	if (pipes->next != NULL)
		execute_child(pipes, pipes, env);
	else
		return (execute_single(pipes, env));
	return (0);
}
