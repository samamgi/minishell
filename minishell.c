/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadi-ou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 19:02:50 by ssadi-ou          #+#    #+#             */
/*   Updated: 2025/05/03 20:35:25 by ssadi-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	operators(char c)
{
	return (c == '>' || c == '<' || c == '|');
}

int	words(char c)
{
	return (!operators(c) && c != '"' && c != '\'' && (!((c >= 9 && c <= 13) || c == 32)));
}

void	tokenizer(t_token **lst, char *token, t_token_type type)
{
	t_token	*str;
	t_token	*current;

	str = (t_token *)malloc(sizeof(t_token));
	if (!str)
		return ;
	str->value = token;
	str->type = type;
	str->single_quotes = false;
	str->double_quotes = false;
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

char	*quotes(char *line, int *i)
{
	char	quote;
	int		len;
	int		start;

	quote = line[*i];
	len = 0;
	start = ++(*i);
	while (line[*i] && line[*i] != quote)
	{
		line[*i] *= -1;
		(*i)++;
		len++;
	}
	if (line[*i] == quote)
		(*i)++;
	return (ft_substr(line, start, len));
}

char	*word(char *line, int *i)
{
	int	start;

	start = *i;
	while (line[*i] && !operators(line[*i]) && line[*i] != '"' && line[*i] != '\'' && (!((line[*i] >= 9 && line[*i] <= 13) || line[*i] == 32)))
		(*i)++;
	return (ft_substr(line, start, ((*i) - start)));
}

void	set_tokens(char *line)
{
	t_token	*lst;
	t_token	*current;
	int		i;

	i = 0;
	lst = NULL;
	while (line[i])
	{
		while (line[i] && ((line[i] >= 9 && line[i] <= 13) || line[i] == 32))
			i++;
		if (!line[i])
			break ;
		if (line[i] && line[i] == '>' && line[i + 1] == '>')
		{
                        tokenizer(&lst, ft_substr(line, i, 2), T_REDIR_APPEND);
			i += 2;
			continue;
		}
		if (line[i] && line[i] == '<' && line[i + 1] == '<')
		{
                        tokenizer(&lst, ft_substr(line, i, 2), T_HEREDOC);
			i += 2;
			continue;
		}
		if (line[i] && line[i] == '>')
		{
			tokenizer(&lst, ft_substr(line, i++, 1), T_REDIR_OUT);
			continue;
		}
		if (line[i] && line[i] == '<')
		{
			tokenizer(&lst, ft_substr(line, i++, 1), T_REDIR_IN);
			continue;
		}
		if (line[i] && line[i] == '|')
		{
			tokenizer(&lst, ft_substr(line, i++, 1), T_PIPE);
			continue;
		}
		if (line[i] && (line[i] == '"' || line[i] == '\''))
		{
                	tokenizer(&lst, quotes(line, &i), T_WORD);
			continue;
		}
		if (line[i] && words(line[i]))
		{
			tokenizer(&lst, word(line, &i), T_WORD);
			continue;
		}
		else
			i++;
	}
	current = lst;
	while (current)
	{
		if (current->type == T_REDIR_OUT)
			ft_printf("type = REDIR_OUT\n");
		if (current->type == T_REDIR_IN)
			ft_printf("type = REDIR_IN\n");
		if (current->type == T_PIPE)
			ft_printf("type = PIPE\n");
		if (current->type == T_REDIR_APPEND)
			ft_printf("type = REDIR_APPEND\n");
		if (current->type == T_HEREDOC)
			ft_printf("type = HERE_DOC\n");
		if (current->type == T_WORD)
			ft_printf("type = WORD\n");
		ft_printf("value = %s\n\n", current->value);
		current = current->next;
	}
}

int	main(int ac, char **av)
{
	char	*line;

	(void)av;
	(void)ac;
	while (1)
	{
		line = readline("minishell: ");
		if (ft_strnstr(line, "exit", 4))
		{
			free(line);
			break ;
		}
		if (syntax_checker(line) == 1)
			set_tokens(line);
		free(line);
	}
	return (0);
}
