/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aymen <aymen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 23:54:49 by ssadi-ou          #+#    #+#             */
/*   Updated: 2026/03/05 22:55:01 by aymen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../inc/pipex.h"

static void	wait_for_children(pid_t last_pid);

static pid_t	fork_and_exec(t_cmd *pipes, t_cmd *cur, char **env, int *fds)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		signal_child();
		setup_child_fds(cur, fds[0], &fds[1]);
		close_pipes(fds[0], &fds[1], cur);
		commande(env, pipes, cur);
		exit(1);
	}
	return (pid);
}

static void	execute_child(t_cmd *pipes, t_cmd *current, char **env)
{
	int		fds[3];
	pid_t	last_pid;

	fds[0] = -1;
	last_pid = -1;
	while (current)
	{
		if (current->next && pipe(&fds[1]) == -1)
		{
			perror("pipe");
			exit(1);
		}
		last_pid = fork_and_exec(pipes, current, env, fds);
		if (fds[0] != -1)
			close(fds[0]);
		if (current->next)
		{
			close(fds[2]);
			fds[0] = fds[1];
		}
		current = current->next;
	}
	wait_for_children(last_pid);
}

static void	wait_for_children(pid_t last_pid)
{
	pid_t	waited;
	int		status;

	status = 0;
	while (1)
	{
		waited = waitpid(-1, &status, 0);
		if (waited == -1)
			break ;
		if (waited == last_pid)
		{
			if (WIFEXITED(status))
				g_shell.signumber = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				g_shell.signumber = 128 + WTERMSIG(status);
		}
	}
}

static int	execute_single(t_cmd *pipes, char **env)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		signal_child();
		solochild(pipes, env);
	}
	if (waitpid(pid, &status, 0) != -1)
	{
		if (WIFEXITED(status))
			g_shell.signumber = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			g_shell.signumber = 128 + WTERMSIG(status);
	}
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
