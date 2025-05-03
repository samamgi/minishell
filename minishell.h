/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadi-ou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 01:24:15 by ssadi-ou          #+#    #+#             */
/*   Updated: 2025/05/03 17:05:59 by ssadi-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "ft_printf/ft_printf.h"
# include "libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>

int		space(char c);

void	msg_syntax_error(char c);

int		check_cote(char *line);

int		check_else(char *line);

int		check_chevron(char *line);

int		check_pipe(char *line);

int		syntax_checker(char *line);

typedef enum e_token_type
{
	T_WORD,
	T_PIPE,
	T_REDIR_IN,
	T_REDIR_OUT,
	T_REDIR_APPEND,
	T_HEREDOC
}	t_token_type;

typedef struct s_token
{
	char		*value;
	t_token_type	type;
	bool	single_quotes;
	bool	double_quotes;
	struct s_token	*next;
}	t_token;

#endif
