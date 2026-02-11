/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadi-ou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 00:00:00 by ssadi-ou          #+#    #+#             */
/*   Updated: 2026/02/11 00:00:00 by ssadi-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	read_heredoc_content(char *delimiter, int write_fd)
{
	char	*line;
	int		delim_len;

	delim_len = ft_strlen(delimiter);
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			ft_printf("warning: here-document delimited by end-of-file\n");
			break ;
		}
		if (ft_strncmp(line, delimiter, delim_len) == 0
			&& line[delim_len] == '\0')
		{
			free(line);
			break ;
		}
		write(write_fd, line, ft_strlen(line));
		write(write_fd, "\n", 1);
		free(line);
	}
	return (1);
}

static int	setup_heredoc(t_redir *redir)
{
	int	pipefd[2];

	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		return (0);
	}
	if (!read_heredoc_content(redir->file, pipefd[1]))
	{
		close(pipefd[0]);
		close(pipefd[1]);
		return (0);
	}
	close(pipefd[1]);
	redir->heredoc_fd = pipefd[0];
	return (1);
}

static void	process_cmd_heredocs(t_cmd *cmd)
{
	t_redir	*redir;

	if (!cmd)
		return ;
	redir = cmd->redir;
	while (redir)
	{
		if (redir->type == T_HEREDOC)
		{
			if (!setup_heredoc(redir))
			{
				ft_printf("Error: heredoc setup failed\n");
				return ;
			}
		}
		redir = redir->next;
	}
}

void	prepare_heredocs(t_cmd *pipes)
{
	t_cmd	*current;

	current = pipes;
	while (current)
	{
		process_cmd_heredocs(current);
		current = current->next;
	}
}
