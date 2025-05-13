/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadi-ou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 19:02:50 by ssadi-ou          #+#    #+#             */
/*   Updated: 2025/05/13 05:20:32 by ssadi-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*int	operators(char c)
{
	return (c == '>' || c == '<' || c == '|');
}

int	words(char c)
{
	t_token	*str;
	t_token	*current;

	return (!operators(c) && (!((c >= 9 && c <= 13) || c == 32)));
}*/
/*void	tokenizer(t_token **lst, char *token, t_token_type type)
{
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
}*/
/*char	*word_else(char *line, int *i, int *start)
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
	t_token	*current;
	t_token	*tmp;
	int		i;

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
}*/
/*void	token_clear(t_token *lst)
{
	i = 0;
	current = lst;
	while (current)
	{
		tmp = current;
		current = current->next;
		free(tmp->value);
		free(tmp);
	}
}*/
/*void	set_word(char *line, int *i, t_token **lst)
{
	tokenizer(lst, word(line, i), T_CMD);
	while (line[*i] && words(line[*i]))
		tokenizer(lst, word(line, i), T_ARG);
}*/
/*void	set_rdappend(char *line, int *i, t_token **lst)
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
	t_token	*lst;
	int		i;
	t_token	*current;
	char	*line;
	t_token	*lst;

	tokenizer(lst, ft_substr(line, (*i), 1), T_PIPE);
	(*i)++;
}*/
// void	set_tokens_util(char *line, int *i, t_token **lst)
// {
// 	if (line[*i] && words(line[*i]))
// 		return (set_word(line, i, lst));
// 	if (line[*i] && line[*i] == '>' && line[(*i) + 1] == '>')
// 		return (set_rdappend(line, i, lst));
// 	if (line[*i] && line[*i] == '<' && line[(*i) + 1] == '<')
// 		return (set_heredoc(line, i, lst));
// 	if (line[*i] && line[*i] == '>')
// 		return (set_rdout(line, i, lst));
// 	if (line[*i] && line[*i] == '<')
// 		return (set_rdin(line, i, lst));
// 	if (line[*i] && line[*i] == '|')
// 		return (set_pipe(line, i, lst));
// 	else
// 		(*i)++;
// }
// void	token_set_quotes(t_token *lst)
// {
// 	t_token	*current;
// 	int		i;
// 	if (!lst)
// 		return ;
// 	current = lst;
// 	while (current)
// 	{
// 		i = 0;
// 		while ((current->value)[i])
// 		{
// 			if ((current->value)[i] < 0)
// 				(current->value)[i] *= -1;
// 			i++;
// 		}
// 		current = current->next;
// 	}
// }
/*t_token	*set_tokens(char *line)
{
	if (ft_strlen(line) == 0)
		return (NULL);
	i = 0;
	lst = NULL;
	while (line[i])
	{
		while (line[i] && ((line[i] >= 9 && line[i] <= 13) || line[i] == 32))
			i++;
		if (!line[i])
			break ;
		set_tokens_util(line, &i, &lst);
	}
	token_set_quotes(lst);
	return (lst);
}*/
/*void	print_token(t_token *lst)
{
	if (!lst)
		return ;
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
}*/
int	main(int ac, char **av)
{
	char	*line;
	t_token	*lst;

	(void)av;
	(void)ac;
	while (1)
	{
		line = readline("minishell: ");
		if (ft_strnstr(line, "exit", 4))
		{
			free(line);
			return (0);
		}
		if (syntax_checker(line) == 1)
		{
			line = expand_variables(line);
			lst = set_tokens(line);
			free(line);
			print_token(lst);
			token_clear(lst);
		}
	}
	return (0);
}
