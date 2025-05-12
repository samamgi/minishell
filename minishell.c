/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadi-ou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 19:02:50 by ssadi-ou          #+#    #+#             */
/*   Updated: 2025/05/12 20:48:28 by ssadi-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	operators(char c)
{
	return (c == '>' || c == '<' || c == '|');
}

int	words(char c)
{
	return (!operators(c) && (!((c >= 9 && c <= 13) || c == 32)));
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
	char	*substr;

	while (line[*i] && ((line[*i] >= 9 && line[*i] <= 13) || line[*i] == 32))
		(*i)++;
	start = *i;
	if (line[*i] && (line[*i] == '\'' || line[*i] == '"'))
	{
		(*i)++;
		start++;
		while (line[*i] && line[*i] != '\'' && line[*i] != '"' && (!((line[*i] >= 9 && line[*i] <= 13) || line[*i] == 32)))
			(*i)++;
		substr = ft_substr(line, start, ((*i) - (start)));
		if (line[*i] && (line[*i] == '"' || line[*i] == '\''))
			(*i)++;
		return (substr);
	}
	else
	{
		while (line[*i] && !operators(line[*i]) && (!((line[*i] >= 9 && line[*i] <= 13) || line[*i] == 32)))
			(*i)++;
		return (ft_substr(line, start, ((*i) - (start))));
	}
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
		if (line[i] && words(line[i]))
		{
			tokenizer(&lst, word(line, &i), T_CMD);
			while (line[i] && ((line[i] >= 9 && line[i] <= 13) || line[i] == 32))
                        	i++;
			while (line[i] && words(line[i]))
				tokenizer(&lst, word(line, &i), T_ARG);
			continue;
		}
		if (line[i] && line[i] == '>' && line[i + 1] == '>')
                {
                        i += 2;
                        tokenizer(&lst, word(line, &i), T_REDIR_APPEND);
                        continue;
                }
		if (line[i] && line[i] == '<' && line[i + 1] == '<')
		{
			i += 2;
			tokenizer(&lst, word(line, &i), T_HEREDOC);
			continue;
		}
		if (line[i] && line[i] == '>')
                {
                        i++;
                        tokenizer(&lst, word(line, &i), T_REDIR_OUT);
                        continue;
                }
                if (line[i] && line[i] == '<')
                {
                        i++;
                        tokenizer(&lst, word(line, &i), T_REDIR_IN);
		}
		if (line[i] && line[i] == '|')
		{
			tokenizer(&lst, ft_substr(line, i, 1), T_PIPE);
			i++;
		}
		else
			i++;

	}
	current = lst;
	i = 0;
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
		if (current->type == T_CMD)
			ft_printf("type = CMD\n");
		if (current->type == T_ARG)
                        ft_printf("type = ARG\n");
		i = 0;
		while ((current->value)[i])
		{
			if ((current->value)[i] < 0)
				(current->value)[i] *= -1;
			i++;
		}
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
		{
			line = expand_variables(line);
			set_tokens(line);
		}
		free(line);
	}
	return (0);
}

void	set_tokens_bis(char *line)
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
                	tokenizer(&lst, quotes(line, &i), T_CMD);
			continue;
		}
		if (line[i] && words(line[i]))
		{
			tokenizer(&lst, word(line, &i), T_CMD);
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
		if (current->type == T_CMD)
			ft_printf("type = CMD\n");
		if (current->type == T_ARG)
                        ft_printf("type = ARG\n");
		ft_printf("value = %s\n\n", current->value);
		current = current->next;
	}
}
