/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadi-ou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 01:24:15 by ssadi-ou          #+#    #+#             */
/*   Updated: 2025/05/18 21:15:45 by ssadi-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "ft_printf/ft_printf.h"
# include "libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>

int					space(char c);

void				msg_syntax_error(char c);

int					check_cote(char *line);

int					check_else(char *line);

int					check_chevron(char *line);

int					check_pipe(char *line);

int					syntax_checker(char *line);

int					operators(char c);

int					words(char c);

char				*expand_variables(char *line);

void				set_doublecotes(char *line);

typedef enum e_token_type
{
	T_CMD,
	T_ARG,
	T_PIPE,
	T_REDIR_IN,
	T_REDIR_OUT,
	T_REDIR_APPEND,
	T_HEREDOC
}					t_token_type;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	struct s_token	*next;
}					t_token;

typedef struct s_redir
{
	t_token_type	type;
	char			*file;
	int				heredoc_fd;
	struct s_redir	*next;
}					t_redir;

typedef struct s_cmd
{
	char			**args;
	t_redir			*redir;
	struct s_cmd	*next;
}					t_cmd;

void				set_rdappend(char *line, int *i, t_token **lst);

void				set_heredoc(char *line, int *i, t_token **lst);

void				set_rdout(char *line, int *i, t_token **lst);

void				set_rdin(char *line, int *i, t_token **lst);

void				set_pipe(char *line, int *i, t_token **lst);

void				set_word(char *line, int *i, t_token **lst, int *cmd);

void				set_tokens_util(char *line, int *i, t_token **lst,
						int *cmd);

void				token_set_quotes(t_token *lst);

void				print_token(t_token *lst);

void				token_clear(t_token *lst);

void				tokenizer(t_token **lst, char *token, t_token_type type);

char				*word_else(char *line, int *i, int *start);

char				*word(char *line, int *i);

t_token				*set_tokens(char *line);

void				free_split(char **split);

void				free_redir(t_redir *redir);

void				free_cmd(t_cmd *pipe);

void				print_cmd_util(t_cmd *pipes);

void				print_cmd(t_cmd *pipes);

t_redir				*set_redir(t_token_type token, char *value);

t_cmd				*init_pipes(t_token *lst);

int					token_count(t_token *lst);

int					set_args(t_cmd *pipes, t_token *lst);

void				cmd_set_redir(t_cmd *pipes, t_token **current,
						t_redir **next);

t_cmd				*parse_tokens(t_token *lst);

void				parse_all_util2(t_token **tmp, t_token **current);

void				parse_all_util(t_cmd **pipes, t_token **tmp,
						t_token **start, t_token **current);

t_cmd				*parse_all(t_token *lst);

int					pipex(t_cmd *pipes, char **env);

void				child1(t_cmd *pipes, char **env);

void				set_fd(t_cmd *pipes);

void				ft_free(void *ptr);

void				prepare_heredocs(t_cmd *pipes);

#endif
