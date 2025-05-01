/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadi-ou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 05:30:15 by ssadi-ou          #+#    #+#             */
/*   Updated: 2025/05/18 21:14:20 by ssadi-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../../minishell.h"
# include "../libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_exec
{
	char	*slash;
	char	**split_path;
	char	**env;
	t_cmd	*pipes;
	t_cmd	*current;
}			t_exec;

int			check_exist(char *cmd);

char		*getpath(char **env);

void		put_error(char *path, int error, char **argv);

char		*pathfinder(char *slash, char **split_path);

void		commande(char **env, t_cmd *pipes, t_cmd *current);

void		execlast(t_exec *exec);

int			execslash(char *cmd, t_cmd *current, char *path, char **env);

void		freeall(char *slash, char *path, char **split_path);

int			open_redir_in(char *file);

int			open_redir_out(char *file, t_token_type type);

int			handle_redir(t_redir *redir);

void		set_fd(t_cmd *pipes);

void		solochild(t_cmd *pipes, char **env);

void		setup_child_fds(t_cmd *current, int prev_pipe, int *pipefd);

void		close_pipes(int prev_pipe, int *pipefd, t_cmd *current);

#endif
