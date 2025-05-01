/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_util2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadi-ou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 23:24:32 by ssadi-ou          #+#    #+#             */
/*   Updated: 2026/02/10 23:36:14 by ssadi-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../inc/pipex.h"

void	set_fd(t_cmd *pipes)
{
	t_redir	*current;

	current = pipes->redir;
	while (current)
	{
		if (!handle_redir(current))
		{
			free_cmd(pipes);
			exit(1);
		}
		current = current->next;
	}
}

void	solochild(t_cmd *pipes, char **env)
{
	set_fd(pipes);
	if (pipes->args[0])
		commande(env, pipes, pipes);
	else
	{
		free_cmd(pipes);
		exit(0);
	}
}

static int	handle_redir_type(t_redir *r, int is_input)
{
	int	handled;

	handled = 0;
	while (r)
	{
		if (is_input && (r->type == T_REDIR_IN || r->type == T_HEREDOC))
		{
			if (!handle_redir(r))
				exit(1);
			handled = 1;
		}
		else if (!is_input && (r->type == T_REDIR_OUT
				|| r->type == T_REDIR_APPEND))
		{
			if (!handle_redir(r))
				exit(1);
			handled = 1;
		}
		r = r->next;
	}
	return (handled);
}

void	setup_child_fds(t_cmd *current, int prev_pipe, int *pipefd)
{
	int		in_handled;
	int		out_handled;

	in_handled = handle_redir_type(current->redir, 1);
	out_handled = handle_redir_type(current->redir, 0);
	if (!in_handled && prev_pipe != -1)
		dup2(prev_pipe, STDIN_FILENO);
	if (!out_handled && current->next)
		dup2(pipefd[1], STDOUT_FILENO);
}

void	close_pipes(int prev_pipe, int *pipefd, t_cmd *current)
{
	if (prev_pipe != -1)
		close(prev_pipe);
	if (current->next)
	{
		close(pipefd[0]);
		close(pipefd[1]);
	}
}
