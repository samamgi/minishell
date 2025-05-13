/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sets2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadi-ou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 05:13:13 by ssadi-ou          #+#    #+#             */
/*   Updated: 2025/05/13 05:15:10 by ssadi-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	set_word(char *line, int *i, t_token **lst)
{
	tokenizer(lst, word(line, i), T_CMD);
	while (line[*i] && words(line[*i]))
		tokenizer(lst, word(line, i), T_ARG);
}

void	set_tokens_util(char *line, int *i, t_token **lst)
{
	if (line[*i] && words(line[*i]))
		return (set_word(line, i, lst));
	if (line[*i] && line[*i] == '>' && line[(*i) + 1] == '>')
		return (set_rdappend(line, i, lst));
	if (line[*i] && line[*i] == '<' && line[(*i) + 1] == '<')
		return (set_heredoc(line, i, lst));
	if (line[*i] && line[*i] == '>')
		return (set_rdout(line, i, lst));
	if (line[*i] && line[*i] == '<')
		return (set_rdin(line, i, lst));
	if (line[*i] && line[*i] == '|')
		return (set_pipe(line, i, lst));
	else
		(*i)++;
}

void	token_set_quotes(t_token *lst)
{
	t_token	*current;
	int		i;

	if (!lst)
		return ;
	current = lst;
	while (current)
	{
		i = 0;
		while ((current->value)[i])
		{
			if ((current->value)[i] < 1)
				(current->value)[i] *= -1;
			i++;
		}
		current = current->next;
	}
}
