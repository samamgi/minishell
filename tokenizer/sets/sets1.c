/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sets.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadi-ou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 05:10:24 by ssadi-ou          #+#    #+#             */
/*   Updated: 2025/05/13 05:12:00 by ssadi-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	set_rdappend(char *line, int *i, t_token **lst)
{
	(*i) += 2;
	tokenizer(lst, word(line, i), T_REDIR_APPEND);
}

void	set_heredoc(char *line, int *i, t_token **lst)
{
	(*i) += 2;
	tokenizer(lst, word(line, i), T_HEREDOC);
}

void	set_rdout(char *line, int *i, t_token **lst)
{
	(*i)++;
	tokenizer(lst, word(line, i), T_REDIR_OUT);
}

void	set_rdin(char *line, int *i, t_token **lst)
{
	(*i)++;
	tokenizer(lst, word(line, i), T_REDIR_IN);
}

void	set_pipe(char *line, int *i, t_token **lst)
{
	tokenizer(lst, ft_substr(line, (*i), 1), T_PIPE);
	(*i)++;
}
