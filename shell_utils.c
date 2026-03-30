/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aymen <aymen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 00:00:00 by aymen             #+#    #+#             */
/*   Updated: 2026/03/30 00:00:00 by aymen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	increment_shlvl(t_env **env_list)
{
	char	*shlvl_str;
	int		shlvl_val;
	char	*new_shlvl;

	shlvl_str = get_env_value(*env_list, "SHLVL");
	if (shlvl_str)
		shlvl_val = ft_atoi(shlvl_str) + 1;
	else
		shlvl_val = 1;
	new_shlvl = ft_itoa(shlvl_val);
	if (!new_shlvl)
		return ;
	set_env_value(env_list, "SHLVL", new_shlvl);
	free(new_shlvl);
}

void	update_last_arg(t_env **env_list, char *cmd)
{
	if (cmd)
		set_env_value(env_list, "_", cmd);
}

static int	restore_std_fds(int saved_stdin, int saved_stdout, int status)
{
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
	return (status);
}

static int	apply_one_redir(t_redir *redir)
{
	int	fd;

	if (redir->type == T_HEREDOC)
		fd = redir->heredoc_fd;
	else if (redir->type == T_REDIR_IN)
		fd = open(redir->file, O_RDONLY, 0644);
	else if (redir->type == T_REDIR_OUT)
		fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		return (1);
	if (redir->type == T_REDIR_OUT || redir->type == T_REDIR_APPEND)
		dup2(fd, STDOUT_FILENO);
	else
		dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

int	apply_redir_builtin(t_cmd *pipes, t_env **env_list)
{
	int		saved_stdin;
	int		saved_stdout;
	t_redir	*redir;
	int		result;

	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	if (saved_stdin == -1 || saved_stdout == -1)
		return (-1);
	redir = pipes->redir;
	while (redir)
	{
		if (apply_one_redir(redir))
			return (restore_std_fds(saved_stdin, saved_stdout, -1));
		redir = redir->next;
	}
	result = execute_builtin(pipes, env_list);
	g_shell.signumber = result;
	return (restore_std_fds(saved_stdin, saved_stdout, result));
}
