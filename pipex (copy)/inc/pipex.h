/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadi-ou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 05:30:15 by ssadi-ou          #+#    #+#             */
/*   Updated: 2025/05/18 16:04:33 by ssadi-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

int		check_exist(char *cmd);

char	*getpath(char **env);

void	put_error(char *path, int error, char **argv);

char	*pathfinder(char *slash, char **split_path);

void	commande(char **cmd, char **env);

void	execlast(char *slash, char **split_path, char **argv, char **env);

int		execslash(char *cmd, char **av, char *path, char **env);

void	freeall(char *slash, char *path, char **split_path, char **argv);

typedef enum e_token_type
{
        T_CMD,
        T_ARG,
        T_PIPE,
        T_REDIR_IN,
        T_REDIR_OUT,
        T_REDIR_APPEND,
        T_HEREDOC
}                                       t_token_type;

typedef struct s_token
{
        char                    *value;
        t_token_type    type;
        struct s_token  *next;
}                                       t_token;

typedef struct s_redir
{
        t_token_type    type;
        char                    *file;
        struct s_redir  *next;
}                                       t_redir;

typedef struct s_cmd
{
        char                    **args;
        t_redir                 *redir;
        struct s_cmd    *next;
}                                       t_cmd;

#endif
