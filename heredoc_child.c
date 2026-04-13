/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_child.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aymen <aymen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 00:00:00 by aymen             #+#    #+#             */
/*   Updated: 2026/03/30 00:00:00 by aymen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	heredoc_child_exit(int status, int write_fd, t_cmd *cmd_root,
		t_env *env_list)
{
	if (write_fd >= 0)
		close(write_fd);
	if (cmd_root)
		free_cmd(cmd_root);
	if (env_list)
		free_env(env_list);
	clear_history();
	rl_clear_history();
	exit(status);
}

static int	is_delimiter(char *line, char *delimiter)
{
	int	delim_len;

	delim_len = ft_strlen(delimiter);
	return (ft_strncmp(line, delimiter, delim_len) == 0
		&& line[delim_len] == '\0');
}

static void	print_heredoc_eof_warning(char *delimiter)
{
	ft_printf("minishell: warning: here-document delimited by end-of-file ");
	ft_printf("(wanted `%s')\n", delimiter);
}

static int	read_heredoc_content(char *delimiter, int write_fd)
{
	char	*line;

	signal_heredoc();
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			if (heredoc_interrupted())
				return (130);
			print_heredoc_eof_warning(delimiter);
			return (1);
		}
		if (is_delimiter(line, delimiter))
			return (free(line), 1);
		write(write_fd, line, ft_strlen(line));
		write(write_fd, "\n", 1);
		free(line);
	}
}

int	run_heredoc_child(int write_fd, t_redir *redir, t_cmd *cmd_root,
		t_env *env_list)
{
	int	hd_status;

	hd_status = read_heredoc_content(redir->file, write_fd);
	if (hd_status == 130)
		heredoc_child_exit(130, write_fd, cmd_root, env_list);
	if (hd_status != 1)
		heredoc_child_exit(1, write_fd, cmd_root, env_list);
	heredoc_child_exit(0, write_fd, cmd_root, env_list);
	return (0);
}
