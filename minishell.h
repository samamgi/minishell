/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadi-ou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 01:24:15 by ssadi-ou          #+#    #+#             */
/*   Updated: 2025/05/07 03:37:23 by ssadi-ou         ###   ########.fr       */
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
	bool			single_quotes;
	bool			double_quotes;
	struct s_token	*next;
}					t_token;

void				set_rdappend(char *line, int *i, t_token **lst);

void				set_heredoc(char *line, int *i, t_token **lst);

void				set_rdout(char *line, int *i, t_token **lst);

void				set_rdin(char *line, int *i, t_token **lst);

void				set_pipe(char *line, int *i, t_token **lst);

void				set_word(char *line, int *i, t_token **lst);

void				set_tokens_util(char *line, int *i, t_token **lst);

void				token_set_quotes(t_token *lst);

void				print_token(t_token *lst);

void				token_clear(t_token *lst);

void				tokenizer(t_token **lst, char *token, t_token_type type);

char				*word_else(char *line, int *i, int *start);

char				*word(char *line, int *i);

t_token				*set_tokens(char *line);

#endif
