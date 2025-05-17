/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadi-ou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 05:19:18 by ssadi-ou          #+#    #+#             */
/*   Updated: 2025/05/13 05:20:26 by ssadi-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	tokenizer(t_token **lst, char *token, t_token_type type)
{
	t_token	*str;
	t_token	*current;

	str = (t_token *)malloc(sizeof(t_token));
	if (!str)
		return ;
	str->value = token;
	str->type = type;
	str->next = NULL;
	if (!*lst)
		*lst = str;
	else
	{
		current = *lst;
		while (current->next)
			current = current->next;
		current->next = str;
	}
}

char	*word_else(char *line, int *i, int *start)
{
	while (line[*i] && !operators(line[*i]) && (!((line[*i] >= 9
					&& line[*i] <= 13) || line[*i] == 32)))
		(*i)++;
	while (line[*i] && ((line[*i] >= 9 && line[*i] <= 13) || line[*i] == 32))
		(*i)++;
	return (ft_substr(line, (*start), ((*i) - (*start))));
}

char	*word(char *line, int *i)
{
	int		start;
	char	*substr;

	while (line[*i] && ((line[*i] >= 9 && line[*i] <= 13) || line[*i] == 32))
		(*i)++;
	start = *i;
	if (line[*i] && (line[*i] == '\'' || line[*i] == '"'))
	{
		(*i)++;
		start++;
		while (line[*i] && line[*i] != '\'' && line[*i] != '"'
			&& (!((line[*i] >= 9 && line[*i] <= 13) || line[*i] == 32)))
			(*i)++;
		substr = ft_substr(line, start, ((*i) - (start)));
		if (line[*i] && (line[*i] == '"' || line[*i] == '\''))
			(*i)++;
		while (line[*i] && ((line[*i] >= 9 && line[*i] <= 13)
				|| line[*i] == 32))
			(*i)++;
		return (substr);
	}
	else
		return (word_else(line, i, &start));
}

t_token	*set_tokens(char *line)
{
	t_token	*lst;
	int		i;
	int		cmd;

	if (ft_strlen(line) == 0)
		return (NULL);
	i = 0;
	lst = NULL;
	cmd = 1;
	while (line[i])
	{
		while (line[i] && ((line[i] >= 9 && line[i] <= 13) || line[i] == 32))
			i++;
		if (!line[i])
			break ;
		set_tokens_util(line, &i, &lst, &cmd);
	}
	token_set_quotes(lst);
	return (lst);
}
