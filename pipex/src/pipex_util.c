/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadi-ou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 23:22:45 by ssadi-ou          #+#    #+#             */
/*   Updated: 2026/02/10 23:32:24 by ssadi-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../inc/pipex.h"

int	open_redir_in(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY, 0644);
	if (fd == -1)
		perror(file);
	return (fd);
}

int	open_redir_out(char *file, t_token_type type)
{
	int	fd;

	if (type == T_REDIR_OUT)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		perror(file);
	return (fd);
}

int	handle_redir(t_redir *redir)
{
	int	fd;

	if (redir->type == T_HEREDOC)
	{
		if (redir->heredoc_fd == -1)
			return (0);
		dup2(redir->heredoc_fd, STDIN_FILENO);
		close(redir->heredoc_fd);
	}
	else if (redir->type == T_REDIR_IN)
	{
		fd = open_redir_in(redir->file);
		if (fd == -1)
			return (0);
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	else if (redir->type == T_REDIR_OUT || redir->type == T_REDIR_APPEND)
	{
		fd = open_redir_out(redir->file, redir->type);
		if (fd == -1 || (dup2(fd, STDOUT_FILENO), close(fd), 0))
			return (0);
	}
	return (1);
}
