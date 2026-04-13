/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aymen <aymen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 00:00:00 by ssadi-ou          #+#    #+#             */
/*   Updated: 2026/03/05 21:20:01 by aymen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	run_heredoc_child(int write_fd, t_redir *redir, t_cmd *cmd_root,
		t_env *env_list);

static int	wait_heredoc_child(pid_t pid, int read_fd, int *last_status)
{
	int	status;

	if (waitpid(pid, &status, 0) == -1)
	{
		close(read_fd);
		return (0);
	}
	setup_signal();
	if ((WIFEXITED(status) && WEXITSTATUS(status) == 130)
		|| (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT))
	{
		*last_status = 130;
		close(read_fd);
		return (0);
	}
	if (!WIFEXITED(status) || WEXITSTATUS(status) != 0)
	{
		close(read_fd);
		return (0);
	}
	return (1);
}

static int	start_heredoc_process(int pipefd[2], pid_t *pid)
{
	if (pipe(pipefd) == -1)
		return (perror("pipe"), 0);
	*pid = fork();
	if (*pid == -1)
	{
		perror("fork");
		close(pipefd[0]);
		close(pipefd[1]);
		return (0);
	}
	return (1);
}

static int	setup_heredoc(t_redir *redir, t_cmd *cmd_root, t_env *env_list,
		int *last_status)
{
	int		pipefd[2];
	pid_t	pid;

	if (!start_heredoc_process(pipefd, &pid))
		return (0);
	if (pid == 0)
	{
		close(pipefd[0]);
		run_heredoc_child(pipefd[1], redir, cmd_root, env_list);
	}
	close(pipefd[1]);
	if (!wait_heredoc_child(pid, pipefd[0], last_status))
		return (0);
	redir->heredoc_fd = pipefd[0];
	return (1);
}

static int	process_cmd_heredocs(t_cmd *cmd, t_cmd *cmd_root, t_env *env_list,
		int *last_status)
{
	t_redir	*redir;

	if (!cmd)
		return (1);
	redir = cmd->redir;
	while (redir)
	{
		if (redir->type == T_HEREDOC)
		{
			if (!setup_heredoc(redir, cmd_root, env_list, last_status))
				return (0);
		}
		redir = redir->next;
	}
	return (1);
}

int	prepare_heredocs(t_cmd *pipes, t_env *env_list, int *last_status)
{
	t_cmd	*current;

	current = pipes;
	while (current)
	{
		if (!process_cmd_heredocs(current, pipes, env_list, last_status))
			return (0);
		current = current->next;
	}
	return (1);
}
